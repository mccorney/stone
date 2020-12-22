#ifndef STONE_ANALYSIS_ANALYSIS_H
#define STONE_ANALYSIS_ANALYSIS_H

#include "stone/Analyze/AnalyzeOptions.h"
#include "stone/Core/ASTCtx.h"
#include "stone/Core/Module.h"
#include "stone/Core/Stats.h"

#include <memory>

namespace stone {

class Analysis final {
public:
  AnalyzeOptions analyzeOpts;

private:
  std::unique_ptr<ASTCtx> astCtx;
  std::unique_ptr<stone::Module> m;
  std::unique_ptr<Stats> stats;

public:
  // TODO: Diag *DG;
  Analysis() = delete;
  Analysis(const Analysis &) = delete;
  Analysis(Analysis &&) = delete;
  Analysis &operator=(const Analysis &) = delete;
  Analysis &operator=(Analysis &&) = delete;

public:
  ASTCtx &GetASTCtx() { return *astCtx.get(); }
  stone::Module &GetModule() { return *m.get(); }
  Stats &GetStats() { return *stats.get(); }
};
} // namespace stone
#endif
