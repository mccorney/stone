#ifndef STONE_ANALYSIS_PARSER_H
#define STONE_ANALYSIS_PARSER_H

#include "stone/Analysis/Analysis.h"
#include "stone/Analysis/AnalysisOptions.h"
#include "stone/Analysis/ParserDiagnostic.h"
#include "stone/Core/ASTContext.h"
#include "stone/Core/Context.h"
#include "stone/Core/Module.h"
#include "stone/Core/Stats.h"

#include <memory>

namespace stone {
class Parser;
class Pipeline;

class ParserStats final : public Stats {
  const Parser &parser;

public:
  ParserStats(const Parser &parser) : parser(parser) {}
  void Print() const override;
};

// class ParserDiagnostics final : public Diagnostics { };

class Parser final {
  friend ParserStats;
  Analysis &analysis;
  ParserStats stats;
  Pipeline *pipeline;

public:
  Parser(Analysis &analysis, Pipeline *pipeline = nullptr);

public:
  // Decl
  int ParseTopDecl();

  //
  void ParseDecl();

  void ParseSpaceDecl();

public:
  // Stmt
  void ParseStmt();

public:
  // Expr
  void ParseExpr();
};

} // namespace stone
#endif
