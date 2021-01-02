#include "stone/Compile/Analysis.h"
#include "stone/Compile/Checker.h"
#include "stone/Compile/Frontend.h"
#include "stone/Core/Ret.h"
#include "stone/Public.h"

using namespace Stone::Analysis;

int Stone::Analysis::Check(AnalysisContext &analysis,
                           CompilePipeline *pipeline) {
  return ret::ok;
}
