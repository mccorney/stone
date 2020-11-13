#include "stone/System/System.h"
#include "stone/System/Compiler.h"
#include "stone/System/Run.h"


int stone::Run(const int argc, const char** args) {


	if(argc > 0 && args[0] == "-compile") {
		stone::Run(argc, args, nullptr); 	
	}
	//System S;
	//S.Init(...);
	//return S.Run();

}
int stone::Run(const int argc, const char** args, CompilerConsumer* Consumer) {

	//stone::Compiler(..., nullptr); 
	//Compiler C; 
	//C.Init(Args);
	//return C.Run();
}

