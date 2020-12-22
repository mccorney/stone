#ifndef STONE_ANALYZE_PARSER_H
#define STONE_ANALYZE_PARSER_H

#include "stone/Analyze/Analysis.h"
#include "stone/Analyze/AnalyzeOptions.h"
#include "stone/Analyze/ParserDiagnostic.h"
#include "stone/Core/ASTCtx.h"
#include "stone/Core/Module.h"
#include "stone/Core/Stats.h"

#include <memory>

namespace stone {
class Parser;
class Pipeline;

class ParserStat final : public Stat {
  const Parser &parser;

public:
  ParserStat(const Parser &parser) : parser(parser) {}
  void Print() const override {}
};

class Parser final {
  friend ParserStat;
  Analysis &analysis;
  ParserStat stat;
  Pipeline *pipeline;

public:
  Parser(Analysis &analysis, Pipeline *pipeline = nullptr);

public:
  // Decl
  int ParseTopDecl();

  //
  void ParseDecl();

public:
  // Stmt
  void ParseStmt();

public:
  // Expr
  void ParseExpr();
};

} // namespace stone
#endif
