#include "stone/System/Compiler.h"
#include "stone/Analysis/Analysis.h"
#include "stone/Core/Ret.h"
#include "stone/System/Help.h"

using namespace stone;

Compiler::Compiler(Pipeline *pipeline)
    : Session(compileOpts), compileOpts(langOpts), pipeline(pipeline) {}

bool Compiler::Build(llvm::ArrayRef<const char *> args) {

  excludedFlagsBitmask = opts::NoCompileOption;
  auto argList = BuildArgList(args);
  return true;
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
