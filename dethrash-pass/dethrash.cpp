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

  // Count how many matrices are there in the arguments.
  ValueMap<Argument*, int> matrices;
  iplist<Argument>& arguments = fn.getArgumentList();
  for (iplist<Argument>::iterator it = arguments.begin(); it != arguments.end(); ++it) {
    if (isMatrix(*it)) {
      matrices.insert(pair<Argument*, int>(&*it, matrices.size()));
    }
  }


  // Does not modify the incoming Function.
  return false;
}


bool DethrashPass::isMatrix(const Argument& arg) {
  Type* type = arg.getType();
  return type->isPointerTy() && type->getContainedType(0)->isFloatTy();
}


//
// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
//

char DethrashPass::ID = 0;
RegisterPass<DethrashPass> X("dethrash", "15745: Dethrash matrix operands.");

}
