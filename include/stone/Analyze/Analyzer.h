#ifndef STONE_ANALYSIS_ANALYZER_H
#define STONE_ANALYSIS_ANALYZER_H

#include "stone/Analyze/AnalyzeOptions.h"

namespace stone {
class Pipeline; 
class Analyzer final {
	public:
		int Analyze(Pipeline* P = nullptr);
};

}
#endif 
