#include "stone/System/Compile.h"
#include "stone/Analysis/Analysis.h"
#include "stone/Core/Ret.h"
#include "stone/Gen/Gen.h"
#include "stone/SubSystem.h"
#include "stone/System/Compiler.h"
#include "stone/System/Help.h"

using namespace stone;

int stone::Compile(llvm::ArrayRef<const char *> args, const char *arg0,
                   void *mainAddr, Pipeline *pipeline) {

  Compiler compiler(pipeline);
  if (compiler.Build(args)) {
    if (compiler.Run()) {
      return ret::err;
    }
  }
  // We are not passing the compiler directly, we are pass stone::Context
  return stone::Gen(compiler.GetAnalysis().GetMainModule(), compiler,
                    compiler.compileOpts.genOpts, pipeline);

  return ret::ok;
}
