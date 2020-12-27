#include "stone/System/Compiler.h"
#include "stone/Analysis/Analysis.h"
#include "stone/Core/Ret.h"
using namespace stone;

Compiler::Compiler(Pipeline *pipeline)
    : compileOpts(GetLangOptions()), pipeline(pipeline) {}

/// Parse the given list of strings into an InputArgList.
std::unique_ptr<llvm::opt::InputArgList>
Compiler::BuildArgList(llvm::ArrayRef<const char *> args) {

  return nullptr;
}
void Compiler::PrintCycle() {}

void Compiler::PrintHelp() {}

int Compiler::Run() {

  // return stone::Analysis(GetAnalysis(), pipeline);
  //
  return 0;
}
