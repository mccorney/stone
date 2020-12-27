#include "stone/System/Compile.h"
#include "stone/Analysis/Analysis.h"
#include "stone/Core/Ret.h"
#include "stone/Gen/Gen.h"
#include "stone/SubSystem.h"
#include "stone/System/Compiler.h"
#include "stone/System/Help.h"

using namespace stone;

namespace stone {

int Analysis(Compiler &compiler) {

  // stond::Analysis(compiler.GetAnalysis());
}
int Gen(Compiler &compiler) {}

} // namespace stone

int stone::Compile(llvm::ArrayRef<const char *> args, const char *arg0,
                   void *mainAddr, Pipeline *pipeline) {

  Compiler compiler(pipeline);
  if (compiler.Build(args)) {
    compiler.Run();
  }

  // Perform a quick help check
  // if (compiler.compileOpts.GetAction()->GetKind() == ActionKind::Help) {
  //  return stone::Help(HelpMode::Compiler);
  //}
  // stone::Analysis(compiler.GetAnalysis());
  // This is not needed.
  // if (compiler.Run(pipeline) == ret::err) {
  //  return ret::err;
  //}
  // Transformer transformer;

  // stone::Gen(C.GetAnalysis().GetModule(), C.compilerOpts.genOpts, P);

  return ret::ok;
}
