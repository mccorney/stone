#include "stone/Analyze/Analyze.h"
#include "stone/Analyze/Analysis.h"
#include "stone/Analyze/Analyzer.h"
#include "stone/Core/Ret.h"
#include "stone/SubSystem.h"

int stone::Analyze(Analysis &AS, Pipeline *P) {

  Analyzer A(AS);
  A.Analyze();

  return ret::ok;
}
