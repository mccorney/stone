#ifndef STONE_GEN_BACKEND_H
#define STONE_GEN_BACKEND_H

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
class Pipeline;
class ASTContext;
struct GenOptions;

class Backend final {
public:
  int ToNative(ASTContext &astCtx, llvm::Module *llvmModule,
               const GenOptions &genOpts, Pipeline *pipeline = nullptr);
  bool ToObject();
  bool ToAssembly();
};

} // namespace stone
#endif
