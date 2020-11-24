#include "stone/System/Compiler.h"
#include "stone/Core/Ret.h"
#include "stone/Analyze/Analyze.h"
using namespace stone;


Compiler::Compiler() {
}
void Compiler::Init(llvm::ArrayRef<const char*> Args) {
}
int Compiler::Run(Pipeline* P) {

	return stone::Analyze(GetAnalysis(), P); 
}

