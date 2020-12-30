#ifndef STONE_COMPILE_TRANSFORMER_H
#define STONE_COMPILE_TRANSFORMER_H

#include "stone/Core/ASTContext.h"
#include "stone/Core/Context.h"
#include "stone/Core/LLVM.h"
#include "stone/Core/Module.h"

namespace llvm {
class raw_pwrite_stream;
class GlobalVariable;
class MemoryBuffer;
class Module;
class TargetOptions;
class TargetMachine;
} // namespace llvm

namespace stone {
class CompilePipeline;

class Transformer final {
public:
  llvm::Module *ToIR(stone::Module &langModule,
                     CompilePipeline *pipeline = nullptr);
};

} // namespace stone
#endif
