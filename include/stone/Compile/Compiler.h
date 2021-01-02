#ifndef STONE_COMPILE_COMPILER_H
#define STONE_COMPILE_COMPILER_H

#include "stone/Compile/Analysis.h"
#include "stone/Compile/CompileOptions.h"
#include "stone/Core/SearchPathOptions.h"
#include "stone/Session/Session.h"

#include "llvm/ADT/ArrayRef.h"

using namespace stone::syntax;

namespace stone {
class CompilePipeline;

namespace analysis {

struct CompileInputProfile final {};
struct CompileOutputProfile final {};

class CompileScope final {
  CompileScope(const CompileScope &) = delete;
  void operator=(const CompileScope &) = delete;

public:
  CompileScope();
  ~CompileScope();
  void Enter();
  void Exit();
  void Print();
};

class Compiler final : public Session {
  SrcMgr sm;
  FileMgr fm;
  CompilePipeline *pipeline = nullptr;
  std::unique_ptr<AnalysisContext> analysis;

public:
  CompileOptions compileOpts;

public:
  Compiler(CompilePipeline *pipeline = nullptr);

  /// Parse the given list of strings into an InputArgList.
  bool Build(llvm::ArrayRef<const char *> args) override;

  int Run() override;
  /// Parse the given list of strings into an InputArgList.
  void PrintLifecycle() override;
  void PrintHelp(bool showHidden) override;

public:
  AnalysisContext &GetAnalysisContext() { return *analysis.get(); }

  SearchPathOptions &GetSearchPathOptions() { return compileOpts.spOpts; }
  const SearchPathOptions &GetSearchPathOptions() const {
    return compileOpts.spOpts;
  }

  CompileOptions &GetCompileOptions() { return compileOpts; }
  const CompileOptions &GetCompileOptions() const { return compileOpts; }

  SrcMgr &GetSrcMgr() { return sm; }

protected:
  void ComputeMode(const llvm::opt::DerivedArgList &args) override;
  ModeKind GetDefaultModeKind() override;
  /// TranslateInputArgs - Create a new derived argument list from the input
  /// arguments, after applying the standard argument translations.
  // llvm::opt::DerivedArgList *
  // TranslateInputArgs(const llvm::opt::InputArgList &args) override const;
};
} // namespace analysis
} // namespace stone
#endif
