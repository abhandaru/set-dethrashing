//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#include "dethrash.h"

using std::cout;
using std::endl;
using std::pair;

namespace llvm {

//
// Called by the FunctionPass API in LLVM.
//

void DethrashPass::getAnalysisUsage(AnalysisUsage& au) const {
  au.setPreservesCFG();
}



bool DethrashPass::runOnModule(Module& mod) {
  for (Module::iterator MI = mod.begin(), ME = mod.end(); MI != ME; ++MI) {
    eachFunction(*MI);
  }
  return false;
}


//
// Helper functions.
//
bool DethrashPass::eachFunction(Function& fn) {
  cout << "Function: " << fn.getName().data() << endl;

  // Compute the set of matrices.
  _matrices.clear();
  iplist<Argument>& arguments = fn.getArgumentList();
  for (iplist<Argument>::iterator it = arguments.begin(); it != arguments.end(); ++it) {
    if (isMatrix(*it)) {
      Value* arg = &*it;
      _matrices.insert(pair<Value*, int>(arg, _matrices.size()));
    }
  }
  _operands = _matrices.size();

  // Iterate through the set.
  for (ValueMap<Value*, int>::iterator it = _matrices.begin(),
      ite = _matrices.end(); it != ite; ++it) {
    Value* matrix = it->first;
    int offset = it->second;
    transform(matrix);
  }

  // Does not modify the incoming Function.
  return false;
}


void DethrashPass::transform(Value* matrix) {
  for(Argument::use_iterator it = matrix->use_begin(); it != matrix->use_end(); ++it) {
    if(GetElementPtrInst *inst = dyn_cast<GetElementPtrInst>(*it)) {
      transformPointer(inst);
    }
  }
}


void DethrashPass::transformPointer(GetElementPtrInst* inst) {
  LLVMContext& context = inst->getParent()->getContext();

  Use* add = inst->idx_begin();
  Value* matrix = inst->getPointerOperand();
  Value* index = add->get();
  int offset = _matrices[matrix];

  cout << "Reference to matrix: " << endl;
  matrix->dump();
  index->dump();

  uint64_t float_shift = log2(FLT_PER_BLOCK);
  uint64_t float_mask = ~FLT_PER_BLOCK + 1;

  // Examples of instructions created.
  // ConstantInt* amount = ConstantInt::get(Type::getInt32Ty(context), 3);
  // Instruction* shift = BinaryOperator::Create(Instruction::Shl, index, amount);

  cout << endl;
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
