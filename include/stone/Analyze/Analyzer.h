#ifndef STONE_ANALYSIS_ANALYZER_H
#define STONE_ANALYSIS_ANALYZER_H

#include "stone/Analyze/Analysis.h"

namespace stone {
class Pipeline;

class Analyzer final {
  Analysis &analysis;

public:
  Analyzer(Analysis &analysis);

public:
  int Analyze(Pipeline *pipeline = nullptr);

private:
  int Parse();
  int Check();
};

} // namespace stone
#endif
