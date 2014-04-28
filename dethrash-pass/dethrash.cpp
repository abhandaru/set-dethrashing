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
