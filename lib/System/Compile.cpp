#include "stone/Analyze/Analyze.h"
#include "stone/Gen/Gen.h"
#include "stone/Core/Ret.h"
#include "stone/System/Compile.h"
#include "stone/System/Compiler.h"
#include "stone/SubSystem.h"
#include "stone/System/Help.h"

using namespace stone;

int stone::Compile(llvm::ArrayRef<const char *> Args, const char *Arg0, 
		void *MainAddr, Pipeline *P) {

	if(Args[0] == "-help") {
		stone::Help(HelpMode::Compile); 
		return ret::ok;
	}
	
	Compiler C;
	C.Init(Args);

	if(C.Run(P) == ret::err){
		return ret::err;
	}

	stone::Gen(C.GetAnalysis().GetModule(), C.CompilerOpts.GenOpts, P);

	return ret::ok; 
}


