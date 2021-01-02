#include "stone/Compile/Backend.h"
#include "stone/Compile/GenOptions.h"
#include "stone/Core/Ret.h"
#include "stone/Public.h"

using namespace Stone;
using namespace Stone::Syntax;
using namespace Stone::Backend;

std::unique_ptr<llvm::TargetMachine>
Backend::CreateTargetMachine(const GenOptions &Opts, ASTContext &astCtx) {
  return nullptr;
}
bool Backend::GenObject(llvm::Module *llvmModule, const GenOptions &genOpts,
                        ASTContext &astCtx, llvm::StringRef outputFilename) {
  return true;
}
