#include "stone/Compile/Backend.h"
#include "stone/Compile/GenOptions.h"
#include "stone/Core/Ret.h"
#include "stone/Public.h"

using namespace stone;

std::unique_ptr<llvm::TargetMachine> CreateTargetMachine(const GenOptions &Opts,
                                                         ASTContext &astCtx) {
  return nullptr;
}
bool stone::GenObject(llvm::Module *llvmModule, const GenOptions &genOpts,
                      ASTContext &astCtx, llvm::StringRef outputFilename) {
  return true;
}
