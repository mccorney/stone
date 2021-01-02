#ifndef STONE_COMPILE_ANALYSIS_H
#define STONE_COMPILE_ANALYSIS_H

#include "stone/Compile/CompileOptions.h"
#include "stone/Core/ASTContext.h"
#include "stone/Core/Module.h"
#include "stone/Core/SearchPathOptions.h"

#include <memory>

using namespace stone::syntax;

namespace stone {
namespace analysis {

class AnalysisContext final {
private:
  SrcMgr &sm;
  const CompileOptions &compileOpts;

  std::unique_ptr<ASTContext> ac;
  const stone::Context &ctx;

  mutable ModuleDecl *mainModule = nullptr;
  // StatEngine se;
public:
  AnalysisContext(const stone::Context &ctx, const CompileOptions &compileOpts,
                  SrcMgr &sm);

  AnalysisContext(const AnalysisContext &) = delete;
  AnalysisContext(AnalysisContext &&) = delete;
  AnalysisContext &operator=(const AnalysisContext &) = delete;
  AnalysisContext &operator=(AnalysisContext &&) = delete;

public:
  ASTContext &GetASTContext() { return *ac.get(); }
  // stone::syntax::ModuleDecl &GetModule() { return *md.get(); }
  //
  /// Retrieve the main module containing the files being compiled.
  ModuleDecl *GetMainModule() const;

  /// Replace the current main module with a new one. This is used for top-level
  /// cached code completion.
  void SetMainModule(ModuleDecl *moduleDecl);

  // StatEngine &GetStats() { return *stats.get(); }
};
} // namespace analysis
} // namespace stone
#endif
