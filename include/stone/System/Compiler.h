#ifndef STONE_SYSTEM_COMPILER_H
#define STONE_SYSTEM_COMPILER_H

#include "stone/Analysis/Analysis.h"
#include "stone/Core/SearchPathOptions.h"
#include "stone/System/Action.h"
#include "stone/System/CompileOptions.h"
#include "stone/System/Session.h"

#include "llvm/ADT/ArrayRef.h"

namespace stone {

class Pipeline;
class Compiler final : public Session {

  Pipeline *pipeline = nullptr;
  SrcMgr sm;
  FileMgr fm;
  std::unique_ptr<Analysis> analysis;

public:
  CompileOptions compileOpts;

public:
  Compiler(Pipeline *pipeline = nullptr);

  /// Parse the given list of strings into an InputArgList.
  bool Build(llvm::ArrayRef<const char *> args) override;

  int Run() override;
  /// Parse the given list of strings into an InputArgList.
  void PrintCycle() override;
  void PrintHelp(bool showHidden) override;

public:
  Analysis &GetAnalysis() { return *analysis.get(); }

  SearchPathOptions &GetSearchPathOptions() {
    return compileOpts.searchPathOpts;
  }
  const SearchPathOptions &GetSearchPathOptions() const {
    return compileOpts.searchPathOpts;
  }

  CompileOptions &GetCompileOptions() { return compileOpts; }
  const CompileOptions &GetCompileOptions() const { return compileOpts; }

  SrcMgr &GetSrcMgr() { return sm; }
};

} // namespace stone
#endif
