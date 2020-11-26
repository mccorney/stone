#ifndef STONE_ANALYZE_ANALYZE_H
#define STONE_ANALYZE_ANALYZE_H


namespace stone {
	class Pipeline; 
	class Analysis;
	int Analyze(Analysis& analysis, Pipeline *pipeline = nullptr);
}
#endif 
