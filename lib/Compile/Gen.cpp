#include "stone/Compile/Analysis.h"
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
using namespace Stone::Analysis;

llvm::Module *Stone::Analysis::GenIR(Syntax::ModuleDecl *moduleDecl,
                                     const Context &ctx,
                                     const GenOptions &genOpts,
                                     llvm::StringRef outputModulename) {

  assert(moduleDecl && "No Module");

  Transformer transformer;

  return nullptr;
}
