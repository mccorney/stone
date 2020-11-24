#ifndef STONE_ANALYSIS_CHECK_H
#define STONE_ANALYSIS_CHECK_H

namespace stone {
	class Pipeline; 
	class Analysis;
	int Check(Analysis& AS, Pipeline *P = nullptr);
}
#endif 
