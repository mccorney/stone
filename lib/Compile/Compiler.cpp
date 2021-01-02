#include "stone/Compile/Compiler.h"
#include "stone/Compile/Analysis.h"
#include "stone/Compile/Frontend.h"
#include "stone/Core/Ret.h"

using namespace stone;
using namespace stone::opts;
using namespace stone::analysis;

Compiler::Compiler(CompilePipeline *pipeline)
    : Session(compileOpts), pipeline(pipeline), fm(compileOpts.fsOpts),
      sm(GetDiagEngine(), fm) {

  analysis.reset(new AnalysisContext(*this, compileOpts, GetSrcMgr()));
}

void Compiler::ComputeMode(const llvm::opt::DerivedArgList &args) {
  Session::ComputeMode(args);
}

bool Compiler::Build(llvm::ArrayRef<const char *> args) {

  excludedFlagsBitmask = opts::NoCompileOption;
  auto argList = BuildArgList(args);

  std::unique_ptr<llvm::opt::DerivedArgList> dArgList(
      TranslateInputArgs(*argList));
  // Computer the compiler mode.
  ComputeMode(*dArgList);

  return true;
}

void Compiler::PrintLifecycle() {}

void Compiler::PrintHelp(bool showHidden) {}

int Compiler::Run() {
  // Perform a quick help check
  if (compileOpts.showHelp) {
    // PrintHelp();
  }
  return 0;
}
