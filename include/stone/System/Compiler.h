#ifndef STONE_SYSTEM_COMPILER_H
#define STONE_SYSTEM_COMPILER_H

#include "stone/Analyze/Analysis.h"
#include "stone/System/CompilerOptions.h"

#include "llvm/ADT/ArrayRef.h"

namespace stone {

class Pipeline; 
class Compiler final {
	Pipeline *pipeline = nullptr; 
	// Action that triggers the Compiler; 
	//CompilerAction* Trigger; 
	public: 
	CompilerOptions compilerOpts; 
	std::unique_ptr<Analysis> analysis;
	public:
		Compiler(); 
		void Init(llvm::ArrayRef<const char*> Args);
		int Run(Pipeline* P = nullptr);
	public:
		Analysis &GetAnalysis() { return *analysis.get(); } 
};

}
#endif
