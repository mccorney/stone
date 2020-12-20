#ifndef STONE_ANALYZE_PARSE_H
#define STONE_ANALYZE_PARSE_H

namespace stone {
class Pipeline;
class Analysis;

int Parse(Analysis &analysis, Pipeline *pipeline = nullptr);
} // namespace stone
#endif
