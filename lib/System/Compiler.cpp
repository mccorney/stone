#include "stone/System/Compiler.h"
#include "stone/Core/Ret.h"

using namespace stone;


Compiler::Compiler() {

}

void Compiler::Init(llvm::ArrayRef<const char*> Args) {

}
int Compiler::Run(Pipeline* P) {

	//stone::Analyze(Analysis, P); 

	return ret::ok; 
}

