#ifndef STONE_ANALYZE_PARSER_H
#define STONE_ANALYZE_PARSER_H

#include "stone/Analyze/Analysis.h"
#include "stone/Analyze/AnalyzeOptions.h"
#include "stone/Core/ASTContext.h"
#include "stone/Core/Module.h"

#include <memory>

namespace stone {
class Pipeline;

class Parser final {
  Analysis &AS;

public:
  Parser(Analysis &AS, Pipeline *P = nullptr);

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
