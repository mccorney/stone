#ifndef STONE_ANALYSIS_ANALYSIS_H
#define STONE_ANALYSIS_ANALYSIS_H

#include "stone/Core/ASTContext.h"
#include "stone/Core/Module.h"
#include "stone/Analyze/AnalyzeOptions.h"

#include <memory>

namespace stone {

class Analysis final {
	public:
		AnalyzeOptions AnalyzeOpts;
	private:
		std::unique_ptr<ASTContext> AC; 
		std::unique_ptr<stone::Module> M; 
 
	public:
		//TODO: Diag *DG; 
		Analysis() = delete;
		Analysis(const Analysis&) = delete;
		Analysis(Analysis &&) = delete;
		Analysis &operator=(const Analysis&) = delete;
		Analysis &operator=(Analysis&&) = delete;
	public:
		ASTContext &GetASTContext(){ return *AC.get(); }
		stone::Module &GetModule(){ return *M.get(); }

};
}
#endif 
