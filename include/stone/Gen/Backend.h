#ifndef STONE_GEN_BACKEND_H
#define STONE_GEN_BACKEND_H

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
class ASTContext;
struct GenOptions;

class Backend final {
	public:
		int ToNative(ASTContext& AC, llvm::Module* M, const GenOptions& GenOptions, 
				Pipeline *P = nullptr);
};

}
#endif 


