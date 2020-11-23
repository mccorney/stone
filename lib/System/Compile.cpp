#include "stone/System/Compile.h"
#include "stone/System/Compiler.h"
#include "stone/System/CompilerConsumer.h"

using namespace stone;

/*
static int Compile(Compiler* C, CompilerConsumer* Consumer) {
	return 0;
}
*/



int stone::Compile(llvm::ArrayRef<const char *> Args, const char *Arg0, void *MainAddr, 
			CompilerConsumer *Consumer) {
	//stone::Compiler(..., nullptr); 
	//Compiler C; 
	//C.Init(Args);
	//return C.Run();

	return 0; 
}


