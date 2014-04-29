//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#include "dethrash.h"

using std::cout;
using std::endl;

namespace llvm {

//
// Called by the FunctionPass API in LLVM.
//

bool DethrashPass::runOnFunction(Function& fn) {
  cout << "Function: " << fn.getName().data() << endl << endl;

  // data_transfer_func = 
  ValueMap<Value*, Value*> map;

  // Count how many matrices are there in the arguments.
  iplist<Argument>& arguments = fn.getArgumentList();
  int matrices_count = 0;
  for(iplist<Argument>::iterator it = arguments.begin(); it != arguments.end(); ++it) {
  	// Count the number of float pointers.
  	Type* arg_type = it->getType();
  	if(arg_type->isPointerTy() && arg_type->getContainedType(0)->isFloatTy())
  		matrices_count++;
  }

  // Go through all instructions and add instructions before %arrayidx# instructions.
  for(Function::iterator bb_itr = fn.begin(); bb_itr != fn.end(); ++bb_itr) {
  	for(BasicBlock::iterator inst_itr = bb_itr->begin(); inst_itr != bb_itr->end(); ++inst_itr) {
  		if(inst_itr->getName()->data()) {
  			BinaryOperator* new_inst = BinaryOperator::Create(Instruction::Add);

  		}
  	}
  }


  // Does not modify the incoming Function.
  return false;
}

void DethrashPass::getAnalysisUsage(AnalysisUsage& au) const {
  au.setPreservesCFG();
}


//
// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
//

char DethrashPass::ID = 0;
RegisterPass<DethrashPass> X("dethrash", "15745: Dethrash matrix operands.");

}
