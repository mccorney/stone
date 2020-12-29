#include "stone/System/Compiler.h"
#include "stone/Analysis/Analysis.h"
#include "stone/Core/Ret.h"

using namespace stone;

Compiler::Compiler(Pipeline *pipeline)
    : Session(compileOpts), compileOpts(langOpts), pipeline(pipeline),
      fm(compileOpts.fsOpts), sm(GetDiagEngine(), fm) {

  analysis.reset(new Analysis(*this, GetSearchPathOptions(), GetSrcMgr()));
}

void Compiler::ComputeMID(const llvm::opt::DerivedArgList &args) {
  Session::ComputeMID(args);
}

bool Compiler::Build(llvm::ArrayRef<const char *> args) {

  excludedFlagsBitmask = opts::NoCompileOption;
  auto argList = BuildArgList(args);

  std::unique_ptr<llvm::opt::DerivedArgList> dArgList(
      TranslateInputArgs(*argList));
  // Computer the compiler mode.
  ComputeMID(*dArgList);

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
