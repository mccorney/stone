#ifndef STONE_COMPILE_BACKEND_H
#define STONE_COMPILE_BACKEND_H

#include "stone/Core/ASTContext.h"
#include "stone/Core/LLVM.h"
#include "llvm/Target/TargetMachine.h"

using namespace Stone::Syntax;

namespace llvm {
class raw_pwrite_stream;
class GlobalVariable;
class MemoryBuffer;
class Module;
class TargetOptions;
class TargetMachine;
} // namespace llvm

namespace Stone {
class GenOptions;

namespace Syntax {
class ASTContext;
}
std::unique_ptr<llvm::TargetMachine> CreateTargetMachine(const GenOptions &Opts,
                                                         ASTContext &astCtx);

bool GenObject(llvm::Module *llvmModule, const GenOptions &genOpts,
               ASTContext &astCtx, llvm::StringRef outputFilename);
} // namespace Stone
#endif
