#include "stone/Compile/Gen.h"
#include "stone/Compile/Backend.h"
#include "stone/Compile/GenOptions.h"
#include "stone/Compile/Transformer.h"
#include "stone/Core/ASTContext.h"
#include "stone/Core/Module.h"
#include "stone/Core/Ret.h"
#include "stone/Public.h"

#include "llvm/IR/Module.h"

using namespace stone;

int stone::Gen(stone::ModuleDecl *moduleDecl, const stone::Context &ctx,
               const GenOptions &genOpts, CompilePipeline *pipeline) {

  assert(moduleDecl && "No Module");

  // llvm::Module *llvmModule = stone::ToIR(moduleDecl, pipeline);
  // assert(llvmModule && "No LLVM Module");

  // From Backend.h
  // stone::ToAssembly();
  // stone::ToObject();
  // stone::ToNative(M.GetASTContext(), M, P);

  return ret::ok;
}
