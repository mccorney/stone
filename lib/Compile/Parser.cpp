#include "stone/Compile/Parser.h"
#include "stone/Core/Ret.h"

using namespace Stone;
using namespace Stone::Frontend;

Parser::Parser(Analysis &analysis, CompilePipeline *pipeline)
    : analysis(analysis), pipeline(pipeline), stats(*this) {}

//===----------------------------------------------------------------------===//
// Decl
//===----------------------------------------------------------------------===//
int Parser::ParseTopDecl() { return ret::ok; }

void Parser::ParseDecl() {}
//===----------------------------------------------------------------------===//
// Stmt
//===----------------------------------------------------------------------===//

void Parser::ParseStmt() {}

//===----------------------------------------------------------------------===//
// Expr
//===----------------------------------------------------------------------===//
void Parser::ParseExpr() {}

void ParserStats::Print() const {}
