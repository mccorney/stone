#ifndef STONE_ANALYSIS_ANALYSIS_H
#define STONE_ANALYSIS_ANALYSIS_H

#include "stone/Analyze/AnalyzeOptions.h"
#include "stone/Core/ASTCtx.h"
#include "stone/Core/Module.h"

#include <memory>

namespace stone {

class Analysis final {
public:
  AnalyzeOptions analyzeOpts;

private:
  std::unique_ptr<ASTCtx> ac;
  std::unique_ptr<stone::ModuleDecl> md;
  // StatEngine se;
public:
  Analysis(const LangOptions &langOpts, const SearchPathOptions &searchPathOpts,
           SrcMgr &sm);

  Analysis(const Analysis &) = delete;
  Analysis(Analysis &&) = delete;
  Analysis &operator=(const Analysis &) = delete;
  Analysis &operator=(Analysis &&) = delete;

public:
  ASTCtx &GetASTCtx() { return *ac.get(); }
  stone::ModuleDecl &GetModule() { return *md.get(); }
  // StatEngine &GetStats() { return *stats.get(); }
};
} // namespace stone
#endif
