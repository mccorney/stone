#ifndef STONE_ANALYSIS_PARSE_H
#define STONE_ANALYSIS_PARSE_H

namespace stone {
class Pipeline;
class Analysis;

int Parse(Analysis &analysis, Pipeline *pipeline = nullptr);
} // namespace stone
#endif
