#ifndef STONE_ANALYSIS_ANALYSIS_H
#define STONE_ANALYSIS_ANALYSIS_H

#include "stone/Analysis/AnalysisOptions.h"
#include "stone/Core/ASTContext.h"
#include "stone/Core/Module.h"
#include "stone/Core/SearchPathOptions.h"

#include <memory>

namespace stone {

class Analysis final {
public:
  AnalysisOptions analysisOpts;

private:
  std::unique_ptr<ASTContext> ac;
  const stone::Context &ctx;
  const SearchPathOptions &pathOpts;
  SrcMgr &sm;

  mutable ModuleDecl *mainModule = nullptr;
  // StatEngine se;
public:
  Analysis(const stone::Context &ctx, const SearchPathOptions &pathOpts,
           SrcMgr &sm);

  Analysis(const Analysis &) = delete;
  Analysis(Analysis &&) = delete;
  Analysis &operator=(const Analysis &) = delete;
  Analysis &operator=(Analysis &&) = delete;

public:
  ASTContext &GetASTContext() { return *ac.get(); }
  // stone::ModuleDecl &GetModule() { return *md.get(); }
  //
  /// Retrieve the main module containing the files being compiled.
  ModuleDecl *GetMainModule() const;

  /// Replace the current main module with a new one. This is used for top-level
  /// cached code completion.
  void SetMainModule(ModuleDecl *moduleDecl);

  // StatEngine &GetStats() { return *stats.get(); }
};
} // namespace stone
#endif
