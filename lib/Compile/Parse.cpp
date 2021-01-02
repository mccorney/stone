#include "stone/Core/Ret.h"
#include "stone/Public.h"
#include "stone/Compile/Analysis.h"
#include "stone/Compile/Frontend.h"
#include "stone/Compile/Parser.h"

using namespace Stone::Frontend; 

int Frontend::Parse(Analysis &analysis, CompilePipeline *pipeline) {
  return ret::ok;
}
