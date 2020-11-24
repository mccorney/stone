#ifndef STONE_GEN_TRANSFORMER_H
#define STONE_GEN_TRANSFORMER_H

#include "stone/Core/LLVM.h"
#include "stone/Core/ASTContext.h"

namespace llvm {
  class raw_pwrite_stream;
  class GlobalVariable;
  class MemoryBuffer;
  class Module;
  class TargetOptions;
  class TargetMachine;
}

namespace stone {
class Pipeline;

class Transformer final {
	public:
		llvm::Module *ToLLVM(Pipeline *P = nullptr);
};

}
#endif 


