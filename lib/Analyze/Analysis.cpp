#include "stone/Analyze/Analysis.h"
#include "stone/Core/Mem.h"

using namespace stone;

Analysis::Analysis(const LangOptions &langOpts,
                   const SearchPathOptions &pathOpts, SrcMgr &sm) {

  ac.reset(new ASTContext(langOpts, pathOpts, sm));
}
