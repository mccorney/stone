#ifndef STONE_SYSTEM_COMPILER_H
#define STONE_SYSTEM_COMPILER_H

#include "stone/Analyze/Analysis.h"
#include "stone/System/CompilerOptions.h"

#include "llvm/ADT/ArrayRef.h"

namespace stone {

class Pipeline; 
class Compiler final {
	Pipeline *P = nullptr; 
	// Action that triggers the Compiler; 
	//CompilerAction* Trigger; 
	public: 
	CompilerOptions CompilerOpts; 
	std::unique_ptr<Analysis> AS;
	public:
		Compiler(); 
		void Init(llvm::ArrayRef<const char*> Args);
		int Run(Pipeline* P = nullptr);
	public:
		Analysis &GetAnalysis() { return *AS.get(); } 
};

}
#endif
