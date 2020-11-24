#ifndef STONE_ANALYZE_PARSER_H
#define STONE_ANALYZE_PARSER_H

#include "stone/Core/ASTContext.h"
#include "stone/Core/Module.h"
#include "stone/Analyze/AnalyzeOptions.h"

#include <memory>

namespace stone {

class Parser final {
	Analysis& AS;
	public:
		Parser(Analysis& AS);
};

}
#endif 
