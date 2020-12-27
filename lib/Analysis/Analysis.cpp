#include "stone/Analysis/Analysis.h"
#include "stone/Core/Mem.h"

using namespace stone;

Analysis::Analysis(Context &context, 
		const SearchPathOptions &pathOpts, SrcMgr &sm) {

  ac.reset(new ASTContext(context, pathOpts, sm));
}
