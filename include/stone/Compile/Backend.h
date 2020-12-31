#ifndef STONE_COMPILE_BACKEND_H
#define STONE_COMPILE_BACKEND_H

#include "stone/Core/ASTContext.h"
#include "stone/Core/LLVM.h"

namespace llvm {
class raw_pwrite_stream;
class GlobalVariable;
class MemoryBuffer;
class Module;
class TargetOptions;
class TargetMachine;
} // namespace llvm

namespace stone {
class ASTContext;
class GenOptions;

bool GenObject(llvm::Module *llvmModule, const GenOptions &genOpts,
               ASTContext &astCtx, llvm::StringRef outputFilename);
} // namespace stone
#endif
