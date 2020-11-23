#include "stone/Analyze/Analyze.h"
#include "stone/Gen/Gen.h"
#include "stone/Core/Ret.h"
#include "stone/System/Compile.h"
#include "stone/System/Compiler.h"
#include "stone/SubSys.h"

using namespace stone;

namespace stone {
	int Compile(Compiler& C, Pipeline* P) {
		return ret::ok;
	}
}

int stone::Compile(llvm::ArrayRef<const char *> Args, const char *Arg0, void *MainAddr, 
			Pipeline *P) {
	
	Compiler C;
	C.Init(Args); 

	return stone::Compile(C, P); 
}


