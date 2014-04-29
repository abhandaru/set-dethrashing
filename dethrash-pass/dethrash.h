//
// 15745 - Set Dethrashing
// Authors: Zhe Qian, Prashanth Suresh, Adu Bhandaru
//

#ifndef __DETHRASH_H__
#define __DETHRASH_H__

#include <iostream>
#include <queue>
#include <set>
#include <vector>

#include "llvm/IR/Instructions.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DepthFirstIterator.h"
#include "llvm/ADT/SmallSet.h"
#include "llvm/ADT/ValueMap.h"
#include "llvm/Support/CFG.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Pass.h"

namespace llvm {

class DethrashPass : public FunctionPass {
 public:
  static char ID;
  DethrashPass() : FunctionPass(ID) { };

  // pass API
  virtual bool runOnFunction(Function& fn);
  virtual void getAnalysisUsage(AnalysisUsage& au) const;
};

}

#endif
