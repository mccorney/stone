#ifndef STONE_ANALYZE_CHECKER_H
#define STONE_ANALYZE_CHECKER_H

#include "stone/Core/ASTContext.h"
#include "stone/Core/Module.h"
#include "stone/Analyze/AnalyzeOptions.h"

#include <memory>

namespace stone {

class Checker final {
	Analysis& AS;
	public:
		Checker(Analysis& AS);
};

}
#endif 
