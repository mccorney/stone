#include "stone/Core/Module.h"
#include "stone/Core/Ret.h"
#include "stone/Public.h"
#include "stone/Compile/Frontend.h"
#include "stone/Compile/GenOptions.h"
#include "stone/Compile/Transformer.h"
#include "stone/Core/ASTContext.h"

#include "llvm/IR/Module.h"

using namespace stone;

llvm::Module *stone::GenIR(stone::ModuleDecl *moduleDecl,
                           const stone::Context &ctx, const GenOptions &genOpts,
                           llvm::StringRef outputModulename) {

  assert(moduleDecl && "No Module");

	Transformer transformer; 


  return nullptr;
}
