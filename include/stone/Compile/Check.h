#ifndef STONE_COMPILE_CHECK_H
#define STONE_COMPILE_CHECK_H

namespace stone {
class CompilePipeline;
class Analysis;
int Check(Analysis &analysis, CompilePipeline *pipeline = nullptr);
} // namespace stone
#endif
