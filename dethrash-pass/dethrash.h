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

#include "llvm/ADT/ValueMap.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CFG.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Pass.h"

// Quantities know when pass is compiled on system.
#define L1_BLK_SIZE     64
#define FLT_PER_BLOCK   (L1_BLK_SIZE / sizeof(float))
#define NUM_OPERANDS    3

namespace llvm {

class DethrashPass : public ModulePass {
 public:
  static char ID;
  DethrashPass() : ModulePass(ID) { };

  // pass API
  virtual bool runOnModule(Module& mod);
  virtual void getAnalysisUsage(AnalysisUsage& au) const;

 private:
  bool eachFunction(Module& mod, Function& fn);
  void getOperands(Function& fn);
  void insertHooks(Module& mod, Function& fn);
  void transform();
  void transformPointers(Value* matrix);
  void transformPointer(GetElementPtrInst* inst);
  bool isMatrixMul(Function& fn);
  bool isMatrix(const Argument& arg);
  int log2(int x);

  // data
  ValueMap<Value*, int> _matrices;
  std::vector<Value*> _inputs;
  Value* _output;
  Value* _size;
  Value* _inter;
  int _operands;
};

}

#endif
