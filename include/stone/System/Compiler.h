#ifndef STONE_SYSTEM_COMPILER_H
#define STONE_SYSTEM_COMPILER_H

#include "llvm/ADT/ArrayRef.h"


namespace stone {

class Compiler final {
	// Action that triggers the Compiler; 
	//CompilerAction* Trigger; 
	public: 
	 //CompilerOptions Opts; 
	 //std::unique_ptr<Analyzer> A;
	 //std::unique_ptr<Transformer> A;//no
	public:
		Compiler(); 
		void Init(llvm::ArrayRef<const char*> Args);
		//bool Run(CompilerAction* Trigger);
	public:
		//Analysis *GetAnalysis(); 
};

}
#endif
