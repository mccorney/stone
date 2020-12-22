#ifndef STONE_ANALYZE_CHECKER_H
#define STONE_ANALYZE_CHECKER_H

#include "stone/Analyze/Analysis.h"
#include "stone/Analyze/AnalyzeOptions.h"
#include "stone/Analyze/CheckerDiagnostic.h"
#include "stone/Core/ASTCtx.h"
#include "stone/Core/Module.h"
#include "stone/Core/Stats.h"

#include <memory>

namespace stone {
class Checker;
class Pipeline;

class CheckerStat final : public Stat {
  const Checker &checker;

public:
  CheckerStat(const Checker &checker) : checker(checker) {}
  void Print() const override {}
};

class Checker final {
  friend CheckerStat;
  Analysis &analysis;
  CheckerStat stat;
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
