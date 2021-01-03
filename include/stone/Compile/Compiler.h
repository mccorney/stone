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

public:
  void Enter();
  void Exit();
};

class Compiler final : public Session {
  SrcMgr sm;
  FileMgr fm;
  CompilePipeline *pipeline = nullptr;
  std::unique_ptr<AnalysisContext> analysis;

  /*
          /// Identifies the set of input buffers in the SrcMgr that are
    /// considered main source files.
    llvm::SetVector<unsigned> primaryBufferIDs;

          /// Return whether there is an entry in PrimaryInputs for buffer \p
    BufID. bool IsPrimaryInput(FileID fileID) const { return
    primaryBufferIDs.count(fileID) != 0;
    }

    /// Record in PrimaryBufferIDs the fact that \p BufID is a primary.
    /// If \p BufID is already in the set, do nothing.
    void RecordPrimaryInputBuffer(FileID fileID);
  */

private:
  struct Listener {
    bool OnSourceFile(Compiler &compiler);
    bool OnModule(Compiler &compiler);
  };
  bool Parse(Compiler::Listener *listener);

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
  //
private:
  void Parse();
  void Check();
};
} // namespace analysis
} // namespace stone
#endif
