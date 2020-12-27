#ifndef STONE_SYSTEM_COMPILER_H
#define STONE_SYSTEM_COMPILER_H

#include "stone/Analysis/Analysis.h"
#include "stone/System/Action.h"
#include "stone/System/CompileOptions.h"
#include "stone/System/Session.h"

#include "llvm/ADT/ArrayRef.h"

namespace stone {

class Pipeline;
class Compiler final : public Session {
  Pipeline *pipeline = nullptr;

public:
  CompileOptions compileOpts;
  std::unique_ptr<Analysis> analysis;

protected:
  /// Parse the given list of strings into an InputArgList.
  std::unique_ptr<llvm::opt::InputArgList>
  BuildArgList(llvm::ArrayRef<const char *> args) override;

public:
  Compiler(Pipeline *pipeline = nullptr);

  /// Parse the given list of strings into an InputArgList.
  bool Build(llvm::ArrayRef<const char *> args) override;

  int Run() override;
  /// Parse the given list of strings into an InputArgList.
  void PrintCycle() override;
  void PrintHelp() override;

public:
  Analysis &GetAnalysis() { return *analysis.get(); }
};

} // namespace stone
#endif
