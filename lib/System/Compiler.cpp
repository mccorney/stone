#include "stone/System/Compiler.h"
#include "stone/Core/Ret.h"
#include "stone/Analyze/Analyze.h"
using namespace stone;


Compiler::Compiler() {
}
void Compiler::Init(llvm::ArrayRef<const char*> args) {
}
int Compiler::Run(Pipeline* pipeline) {

	return stone::Analyze(GetAnalysis(), pipeline); 
}

