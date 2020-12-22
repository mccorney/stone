#include "stone/Analyze/Checker.h"
#include "stone/Core/Ret.h"

using namespace stone;

Checker::Checker(Analysis &analysis, Pipeline *pipeline)
    : analysis(analysis), pipeline(pipeline), stats(*this) {}

// Decl
void Checker::CheckDecl() {}

// Stmt
void Checker::CheckStmt() {}

// Expr
void Checker::CheckExpr() {}

void CheckerStats::Print() const {}
