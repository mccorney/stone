#ifndef STONE_ANALYZE_CHECKER_H
#define STONE_ANALYZE_CHECKER_H

#include "stone/Core/ASTContext.h"
#include "stone/Core/Module.h"
#include "stone/Analyze/AnalyzeOptions.h"
#include "stone/Analyze/Analysis.h"

#include <memory>

namespace stone {
class Pipeline; 

class Checker final {
	Analysis& analysis;
	public:
		Checker(Analysis& analysis, Pipeline* pipeline = nullptr);
	public:
		void CheckDecl(); 

	public:
		void CheckStmt();

	public:
		void CheckExpr(); 
};

}
#endif 