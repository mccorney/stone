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
int stone::Compile(llvm::ArrayRef<const char *> Args, const char *Arg0,
                   void *MainAddr, Pipeline *P) {

  if (Args[0] == "-help") {
    stone::Help(HelpMode::Compile);
    return ret::ok;
  }

  Compiler compiler;
  compiler.Init(Args);
  // stone::Analyze(compiler.GetAnalysis());
  // This is not needed.
  if (compiler.Run(P) == ret::err) {
    return ret::err;
  }
  // Transformer transformer;

  // stone::Gen(C.GetAnalysis().GetModule(), C.compilerOpts.genOpts, P);

  return ret::ok;
}
