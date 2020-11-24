#ifndef STONE_ANALYSIS_ANALYSIS_H
#define STONE_ANALYSIS_ANALYSIS_H

#include "stone/Core/ASTContext.h"
#include "stone/Analyze/AnalyzeOptions.h"
#include <memory>

namespace stone {

class Analysis final {
	public:
		AnalyzeOptions AO;
		std::unique_ptr<ASTContext> AC; 
	// Module 
	public:	
		Analysis() = delete;
		Analysis(const Analysis&) = delete;
		Analysis(Analysis &&) = delete;
		Analysis &operator=(const Analysis&) = delete;
		Analysis &operator=(Analysis&&) = delete; 
};
}
#endif 
