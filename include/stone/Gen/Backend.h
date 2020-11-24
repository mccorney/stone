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

class Backend final {
	public:
		int ToObj(llvm::Module* M, Pipeline *P = nullptr);
};

}
#endif 


