#ifndef STONE_ANALYZE_PARSER_H
#define STONE_ANALYZE_PARSER_H

#include "stone/Analyze/Analysis.h"
#include "stone/Analyze/AnalyzeOptions.h"
#include "stone/Analyze/ParserDiagnostic.h"
#include "stone/Core/ASTContext.h"
#include "stone/Core/Module.h"

#include <memory>

namespace stone {
class Pipeline;

class Parser final {
  Analysis &analysis;

public:
  Parser(Analysis &analysis, Pipeline *pipeline = nullptr);

public:
  // Decl
  int ParseTopDecl();
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
