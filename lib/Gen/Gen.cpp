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

int stone::Gen(stone::Module &langModule, const GenOptions &genOpts,
               Pipeline *pipeline) {

  Transformer transformer;
  llvm::Module *llvmModule = transformer.ToIR(langModule, pipeline);

  Backend backend;

  // Native native;

  // backend.ToAssembly();
  // backend.ToObject();
  // B.ToNative(M.GetASTContext(), M, P);

  return ret::ok;
}
