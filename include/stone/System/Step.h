#ifndef STONE_SYSTEM_STEP_H
#define STONE_SYSTEM_STEP_H

#include "stone/Core/List.h"
#include "llvm/ADT/SmallVector.h"

namespace stone {
class Action;

enum class StepKind { Compile, Backend, Link, Assemble };

class Step {
protected:
  const Action &source;

public:
  Step(const Action &source);
  // virtual void Print() = 0;
  // virtual void Trace() = 0;

public:
  const Action &GetSource() const { return source; }
};

class SyncStep : public Step {
public:
  SyncStep(const Action &source);
};

class AsyncStep : public Step {
public:
  AsyncStep(const Action &source);
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

class LinkStep final : public AsyncStep {
public:
  LinkStep(const Action &source);
};

class Steps final : public List<Step> {
public:
  void Print() const;
};

} // namespace stone
#endif
