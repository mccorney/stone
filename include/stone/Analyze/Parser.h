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
