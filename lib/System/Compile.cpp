#include "stone/System/Compile.h"
#include "stone/Analyze/Analyze.h"
#include "stone/Core/Ret.h"
#include "stone/Gen/Gen.h"
#include "stone/SubSystem.h"
#include "stone/System/Compiler.h"
#include "stone/System/Help.h"

using namespace stone;

namespace stone {

int Analyze(Compiler &compiler) {

  // stond::Analyze(compiler.GetAnalysis());
}
int Gen(Compiler &compiler) {}

} // namespace stone

int stone::Compile(llvm::ArrayRef<const char *> args, const char *arg0,
                   void *mainAddr, Pipeline *pipeline) {

  Compiler compiler;
  auto argList = compiler.BuildArgList(args);

  // Perform a quick help check
  if (compiler.compileOpts.GetAction()->GetKind() == ActionKind::Help) {
    return stone::Help(HelpMode::Compile);
  }
  // stone::Analyze(compiler.GetAnalysis());
  // This is not needed.
  if (compiler.Run(pipeline) == ret::err) {
    return ret::err;
  }
  // Transformer transformer;

  // stone::Gen(C.GetAnalysis().GetModule(), C.compilerOpts.genOpts, P);

  return ret::ok;
}
