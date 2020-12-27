#ifndef STONE_GEN_TRANSFORMER_H
#define STONE_GEN_TRANSFORMER_H

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
class Pipeline;

class Transformer final {
public:
  llvm::Module *ToIR(stone::Module &langModule, Pipeline *pipeline = nullptr);
};

} // namespace stone
#endif
