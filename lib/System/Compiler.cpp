#include "stone/System/Compiler.h"
#include "stone/Analyze/Analyze.h"
#include "stone/Core/Ret.h"
using namespace stone;

Compiler::Compiler() {}

/// Parse the given list of strings into an InputArgList.
std::unique_ptr<llvm::opt::InputArgList>
Compiler::BuildArgList(llvm::ArrayRef<const char *> args) {

  return nullptr;
}

int Compiler::Run(Pipeline *pipeline) {

  return stone::Analyze(GetAnalysis(), pipeline);
}
