#ifndef STONE_ANALYZE_ANALYZE_H
#define STONE_ANALYZE_ANALYZE_H

namespace stone {
	class Pipeline; 
	class Analysis;

	int Analyze(Analysis *A, Pipeline *P = nullptr);
}
#endif 
