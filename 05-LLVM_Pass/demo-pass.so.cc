#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

struct DEMOPass : public PassInfoMixin<DEMOPass> {

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {

    LLVMContext &  C = M.getContext();
    Type *         VoidTy = Type::getVoidTy(C);
    FunctionCallee demo_func = M.getOrInsertFunction("__demo_func", VoidTy);

    printf("Demo Pass running!\n");

    for (auto &F : M) {

      for (auto &BB : F) {

        for (auto &I : BB) {

          if (CallInst *call = dyn_cast<CallInst>(&I)) {

            if (GetCallInsFunctionName(call).equals("puts")) {

              IRBuilder<> IRB(&I);
              IRB.CreateCall(demo_func)->setMetadata(M.getMDKindID("nosanitize"),
                                                    MDNode::get(C, None));

            }

          }

        }

      }
    
    }

    return PreservedAnalyses::none();
  }

  static void registerCallbacks(PassBuilder &PB) {

    PB.registerOptimizerLastEPCallback(
      [](ModulePassManager &MPM, OptimizationLevel OL) {

        MPM.addPass(DEMOPass());

      });

  }

  llvm::StringRef GetCallInsFunctionName(CallInst *call) {

    if (Function *func = call->getCalledFunction()) {

      return func->getName();

    } else {

      // Indirect call
      return dyn_cast<Function>(call->getCalledOperand()->stripPointerCasts())
          ->getName();

    }

  }
};

extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK
llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "DEMOPass", "1.0",
          DEMOPass::registerCallbacks};
}

