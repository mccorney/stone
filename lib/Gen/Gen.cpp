#include "stone/Gen/Gen.h"
#include "stone/Core/ASTContext.h"
#include "stone/Core/Module.h"
#include "stone/Core/Ret.h"
#include "stone/Gen/Backend.h"
#include "stone/Gen/GenOptions.h"
#include "stone/Gen/Transformer.h"
#include "stone/SubSystem.h"
#include "llvm/IR/Module.h"

using namespace stone;

int stone::Gen(stone::ModuleDecl *moduleDecl, const stone::Context &ctx,
               const GenOptions &genOpts, Pipeline *pipeline) {

  assert(moduleDecl && "No Module");

  // llvm::Module *llvmModule = stone::ToIR(moduleDecl, pipeline);
  // assert(llvmModule && "No LLVM Module");

  // From Backend.h
  // stone::ToAssembly();
  // stone::ToObject();
  // stone::ToNative(M.GetASTContext(), M, P);

  return ret::ok;
}
