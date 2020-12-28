#include "stone/System/Compiler.h"
#include "stone/Analysis/Analysis.h"
#include "stone/Core/Ret.h"
#include "stone/System/Help.h"

using namespace stone;

Compiler::Compiler(Pipeline *pipeline)
    : Session(compileOpts), compileOpts(langOpts), pipeline(pipeline),
      fm(fsOpts), sm(GetDiagEngine(), fm) {

  analysis.reset(new Analysis(*this, GetSearchPathOptions(), GetSrcMgr()));
}

bool Compiler::Build(llvm::ArrayRef<const char *> args) {

  excludedFlagsBitmask = opts::NoCompileOption;
  auto argList = BuildArgList(args);
  return true;
}

void Compiler::PrintCycle() {}

void Compiler::PrintHelp(bool showHidden) {}

int Compiler::Run() {
  // Perform a quick help check
  if (compileOpts.showHelp) {
    // PrintHelp();
  }
  return 0;
}
