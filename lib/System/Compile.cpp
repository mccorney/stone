#include "stone/Analyze/Analyze.h"
#include "stone/Gen/Gen.h"
#include "stone/Core/Ret.h"
#include "stone/System/Compile.h"
#include "stone/System/Compiler.h"
#include "stone/SubSystem.h"
#include "stone/System/Help.h"

using namespace stone;

namespace stone {


	/// You do not need this. 
	int Compile(Compiler& C, Pipeline* P) {

		//C.Run(P); 
		return ret::ok;
	}
}

int stone::Compile(llvm::ArrayRef<const char *> Args, const char *Arg0, void *MainAddr, 
			Pipeline *P) {

	if(Args[0] == "-help") {
		stone::Help(HelpMode::Compile); 
		return ret::ok;
	}
	
	Compiler C;
	C.Init(Args);
	// C.Run(P); 


	return stone::Compile(C, P); 
}


