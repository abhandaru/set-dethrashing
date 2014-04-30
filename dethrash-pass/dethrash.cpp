//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#include "dethrash.h"

using std::cout;
using std::endl;
using std::pair;
using std::set;
using std::string;

namespace llvm {

//
// Called by the FunctionPass API in LLVM.
//

void DethrashPass::getAnalysisUsage(AnalysisUsage& au) const {
  au.setPreservesCFG();
}


bool DethrashPass::runOnModule(Module& mod) {
  bool modified = false;
  for (Module::iterator MI = mod.begin(), ME = mod.end(); MI != ME; ++MI) {
    modified = modified || eachFunction(mod, *MI);
  }
  return modified;
}


//
// Helper functions.
//
bool DethrashPass::eachFunction(Module& mod, Function& fn) {
  cout << "Function: " << fn.getName().data() << endl;
  if (!isMatrixMul(fn)) {
    return false;
  }

  // Apply the transformation.
  cout << " - Found matrix mul!" << endl;
  getOperands(fn);
  insertHooks(mod, fn);
  transform();

  // Modifies the incoming Function.
  return true;
}


void DethrashPass::insertHooks(Module& mod, Function& fn) {
  LLVMContext& context = mod.getContext();

  Constant* align_const = mod.getOrInsertFunction("hooks_print",
      Type::getVoidTy(context),
      Type::getInt32Ty(context),
      (Type*)NULL);

  Function* align = cast<Function>(align_const);

  BasicBlock& entry = fn.getEntryBlock();
  Instruction* first = &*(entry.getFirstInsertionPt());

  Value* val = ConstantInt::get(Type::getInt32Ty(context), 18);
  ArrayRef<Value*> array(val);
  Instruction *align_call = CallInst::Create(align, array);
  align_call->insertBefore(first);
}


// Compute the set of matrices.
void DethrashPass::getOperands(Function& fn) {
  _matrices.clear();
  iplist<Argument>& arguments = fn.getArgumentList();
  for (iplist<Argument>::iterator it = arguments.begin(); it != arguments.end(); ++it) {
    if (isMatrix(*it)) {
      Value* arg = &*it;
      _matrices.insert(pair<Value*, int>(arg, _matrices.size()));
    }
  }
  _operands = _matrices.size();
}


// Iterate through the set.
void DethrashPass::transform() {
  for (ValueMap<Value*, int>::iterator it = _matrices.begin(),
      ite = _matrices.end(); it != ite; ++it) {
    Value* matrix = it->first;
    int offset = it->second;
    transformPointers(matrix);
  }
}


void DethrashPass::transformPointers(Value* matrix) {
  // Gather instructions we need to replace.
  set<GetElementPtrInst*> iset;
  for(Argument::use_iterator it = matrix->use_begin(); it != matrix->use_end(); ++it) {
    if(GetElementPtrInst *inst = dyn_cast<GetElementPtrInst>(*it)) {
      iset.insert(inst);
    }
  }
  // Apply transformations safely over set iterator.
  for (set<GetElementPtrInst*>::iterator it = iset.begin(),
      ite = iset.end(); it != ite; ++it) {
    GetElementPtrInst* inst = *it;
    transformPointer(inst);
  }
}


void DethrashPass::transformPointer(GetElementPtrInst* inst) {
  LLVMContext& context = inst->getParent()->getContext();

  // Get relevant operands.
  Value* matrix = inst->getPointerOperand();
  Value* index = inst->idx_begin()->get();
  int offset = _matrices[matrix];

  // Get transform parameters.
  uint64_t float_shift = log2(FLT_PER_BLOCK);
  uint64_t float_mask = ~FLT_PER_BLOCK + 1;

  // Set up constant values.
  Value* mask_val = ConstantInt::get(Type::getInt32Ty(context), float_mask);
  Value* shift_val = ConstantInt::get(Type::getInt32Ty(context), float_shift);
  Value* operands_val = ConstantInt::get(Type::getInt32Ty(context), _operands);
  Value* offset_val = ConstantInt::get(Type::getInt32Ty(context), offset);

  // Create transformation math instructions.
  Instruction* temp1 = BinaryOperator::Create(Instruction::And, index, mask_val);
  Instruction* temp2 = BinaryOperator::Create(Instruction::LShr, index, shift_val);
  Instruction* temp3 = BinaryOperator::Create(Instruction::Mul, temp2, operands_val);
  Instruction* temp4 = BinaryOperator::Create(Instruction::Add, temp3, offset_val);
  Instruction* temp5 = BinaryOperator::Create(Instruction::Shl, temp4, shift_val);
  Instruction* new_index = BinaryOperator::Create(Instruction::Add, temp1, temp5);

  // Create new array reference.
  ArrayRef<Value*> arr_ref(new_index);
  GetElementPtrInst* new_inst = GetElementPtrInst::Create(matrix, arr_ref);
  new_inst->setIsInBounds(true);
  new_inst->setName(Twine("dethrash"));

  // Insert operations in the right order.
  temp1->insertBefore(inst);
  temp2->insertAfter(temp1);
  temp3->insertAfter(temp2);
  temp4->insertAfter(temp3);
  temp5->insertAfter(temp4);
  new_index->insertAfter(temp5);
  new_inst->insertAfter(new_index);

  // Clean up old instruction.
  inst->replaceAllUsesWith(new_inst);
  inst->eraseFromParent();
}


// Ideally this information would be passed as metadata through clang.
// We could do this through custom pragmas or other compiler hints.
bool DethrashPass::isMatrixMul(Function& fn) {
  string name = fn.getName().data();
  return name.find("matrix_mul") != string::npos;
}


bool DethrashPass::isMatrix(const Argument& arg) {
  Type* type = arg.getType();
  return type->isPointerTy() && type->getContainedType(0)->isFloatTy();
}


int DethrashPass::log2(int x) {
  int i = 0;
  while (x >>= 1) {
    i++;
  }
  return i;
}


//
// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
//

char DethrashPass::ID = 0;
RegisterPass<DethrashPass> X("dethrash", "15745: Dethrash matrix operands.");

}
