#ifndef STONE_SYSTEM_STEP_H
#define STONE_SYSTEM_STEP_H

#include "stone/Core/List.h"

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Arg.h"
#include "llvm/Option/ArgList.h"

namespace stone {
class Action;

enum class StepKind {
  Compile,
  Backend,
  DynamicLink,
  StaticLink,
  Assemble,
  First = Compile,
  Last = Assemble
};

class Step {
  friend class Compilation;

protected:
  StepKind kind;
  const Action &source;
  const llvm::opt::Arg *intput = nullptr;

public:
  Step(StepKind kind, const Action &source);
  // virtual void Print() = 0;
  // virtual void Trace() = 0;

public:
  const Action &GetSource() const { return source; }
  StepKind GetKind() { return kind; }
};

class SyncStep : public Step {
public:
  SyncStep(StepKind kind, const Action &source);
};

class AsyncStep : public Step {
public:
  AsyncStep(StepKind kind, const Action &source);
};

class CompileStep final : public AsyncStep {
public:
  CompileStep(const Action &source);
};

class BackendStep final : public AsyncStep {
public:
  BackendStep(const Action &source);
};

class AssembleStep final : public AsyncStep {
public:
  AssembleStep(const Action &source);
};

class DynamicLinkStep final : public AsyncStep {
public:
  DynamicLinkStep(const Action &source);
};
class StaticLinkStep final : public AsyncStep {
public:
  StaticLinkStep(const Action &source);
};

class Steps final : public List<Step> {
public:
  void Print() const;
};

} // namespace stone
#endif
