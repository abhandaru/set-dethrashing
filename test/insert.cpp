#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"

#include "llvm/IR/IRBuilder.h"


namespace llvm {
class bishe_insert : public ModulePass {
 public:
  // Data
  static char ID;
  Function *hook;

  // Just call super constructor.
  bishe_insert() : ModulePass(ID) {}

  virtual bool runOnModule(Module& M) {
    LLVMContext& context = M.getContext();

    // Create function object.
    Constant* hookFunc;
    hookFunc = M.getOrInsertFunction("print",
        Type::getVoidTy(context),
        // Type::getInt32Ty(context),
        (Type*)NULL);
    hook = cast<Function>(hookFunc);

    // Run over every function.
    for(Module::iterator F = M.begin(), E = M.end(); F!= E; ++F) {
      for(Function::iterator BB = F->begin(), E = F->end(); BB != E; ++BB) {
        bishe_insert::runOnBasicBlock(BB);
      }
    }
    return false;
  }

  // Helper function for each block.
  virtual bool runOnBasicBlock(Function::iterator& BB) {
    LLVMContext& context = BB->getContext();

    for(BasicBlock::iterator BI = BB->begin(), BE = BB->end(); BI != BE; ++BI) {
      if(LoadInst *CI = dyn_cast<LoadInst>(BI)) {
        // Value* val = ConstantInt::get(Type::getInt32Ty(context), 5);
        // ArrayRef<Value *> array(val);
        Instruction *newInst = CallInst::Create(hook, "");
        BB->getInstList().insert((Instruction*)CI, newInst);
      }
    }
    return true;
  }
};

// Register pass
char bishe_insert::ID = 0;
static RegisterPass<bishe_insert> X("bishe_insert", "test function exist", false, false);

}
