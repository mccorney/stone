#ifndef STONE_SYSTEM_COMPILER_H
#define STONE_SYSTEM_COMPILER_H

#include "llvm/ADT/ArrayRef.h"

namespace stone {

class Pipeline; 
class Compiler final {
	Pipeline *P = nullptr; 
	// Action that triggers the Compiler; 
	//CompilerAction* Trigger; 
	public: 
	 //CompilerOptions Opts; 
	 //std::unique_ptr<Analysis> A;
	public:
		Compiler(); 
		void Init(llvm::ArrayRef<const char*> Args);
		int Run(Pipeline* P = nullptr);
	public:
		//Analysis *GetAnalysis(); 
};

}
#endif
