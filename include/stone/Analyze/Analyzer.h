#ifndef STONE_ANALYSIS_ANALYZER_H
#define STONE_ANALYSIS_ANALYZER_H

#include "stone/Analyze/Analysis.h"

namespace stone {
class Pipeline;

class Analyzer final {
	Analysis& AS; 
	public:
		Analyzer(Analysis& AS); 
	public:
		int Analyze(Pipeline* P = nullptr);
	private:
		int Parse();
		int Check(); 
};

}
#endif 
