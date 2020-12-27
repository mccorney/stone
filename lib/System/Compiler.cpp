#include "stone/System/Compiler.h"
#include "stone/Analysis/Analysis.h"
#include "stone/Core/Ret.h"
#include "stone/System/Help.h"

using namespace stone;

Compiler::Compiler(Pipeline *pipeline)
    : compileOpts(GetLangOptions()), pipeline(pipeline) {}

bool Compiler::Build(llvm::ArrayRef<const char *> args) {

  auto argList = BuildArgList(args);
}

/// Parse the given list of strings into an InputArgList.
std::unique_ptr<llvm::opt::InputArgList>
Compiler::BuildArgList(llvm::ArrayRef<const char *> args) {

  return nullptr;
}
void Compiler::PrintCycle() {}

void Compiler::PrintHelp() {}

int Compiler::Run() {

  // Perform a quick help check
  if (compileOpts.GetAction()->GetKind() == ActionKind::Help) {
    PrintHelp();
  }

  return 0;
}
