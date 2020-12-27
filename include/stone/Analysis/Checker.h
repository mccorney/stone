#ifndef STONE_ANALYSIS_CHECKER_H
#define STONE_ANALYSIS_CHECKER_H

#include "stone/Analysis/Analysis.h"
#include "stone/Analysis/AnalysisOptions.h"
#include "stone/Analysis/CheckerDiagnostic.h"
#include "stone/Core/ASTContext.h"
#include "stone/Core/Context.h"
#include "stone/Core/Module.h"
#include "stone/Core/Stats.h"

#include <memory>

namespace stone {
class Checker;
class Pipeline;

class CheckerStats final : public Stats {
  const Checker &checker;

public:
  CheckerStats(const Checker &checker) : checker(checker) {}
  void Print() const override;
};

class Checker final {
  friend CheckerStats;
  Analysis &analysis;
  CheckerStats stats;
  Pipeline *pipeline;

public:
  Checker(Analysis &analysis, Pipeline *pipeline = nullptr);

public:
  void CheckDecl();

public:
  void CheckStmt();

public:
  void CheckExpr();
};

} // namespace stone
#endif
