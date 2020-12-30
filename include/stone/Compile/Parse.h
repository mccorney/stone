#ifndef STONE_COMPILE_PARSE_H
#define STONE_COMPILE_PARSE_H

namespace stone {
class CompilePipeline;
class Analysis;

int Parse(Analysis &analysis, CompilePipeline *pipeline = nullptr);
} // namespace stone
#endif
