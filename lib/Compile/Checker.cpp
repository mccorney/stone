#include "stone/Compile/Checker.h"
#include "stone/Core/Ret.h"

using namespace stone;

Checker::Checker(Analysis &analysis, CompilePipeline *pipeline)
    : analysis(analysis), pipeline(pipeline), stats(*this) {}

// Decl
void Checker::CheckDecl() {}

// Stmt
void Checker::CheckStmt() {}

// Expr
void Checker::CheckExpr() {}

void CheckerStats::Print() const {}