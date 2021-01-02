#include "stone/Compile/Frontend.h"
#include "stone/Compile/GenOptions.h"

#include "llvm/IR/Module.h"

using namespace Stone;
using namespace Stone::Analysis;

void Stone::Analysis::OptimizeIR(llvm::Module *llvmModule,
                                 const GenOptions &genOpts,
                                 llvm::TargetMachine *targetMachine) {}
