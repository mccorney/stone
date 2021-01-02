#include "stone/Compile/Frontend.h"
#include "stone/Compile/GenOptions.h"
#include "stone/Compile/Transformer.h"
#include "stone/Core/ASTContext.h"
#include "stone/Core/Module.h"
#include "stone/Core/Ret.h"
#include "stone/Public.h"

#include "llvm/IR/Module.h"

using namespace Stone;
using namespace Stone::Syntax;
using namespace Stone::Frontend;

llvm::Module *Stone::Frontend::GenIR(Stone::Syntax::ModuleDecl *moduleDecl,
                                     const Stone::Context &ctx,
                                     const GenOptions &genOpts,
                                     llvm::StringRef outputModulename) {

  assert(moduleDecl && "No Module");

  Transformer transformer;

  return nullptr;
}

/// TODO:
void OptimizeIR(llvm::Module *llvmModule, const GenOptions &genOpts,
                llvm::TargetMachine *targetMachine) {}
