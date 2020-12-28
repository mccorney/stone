#ifndef STONE_SYSTEM_STEP_H
#define STONE_SYSTEM_STEP_H

#include "llvm/ADT/SmallVector.h"

namespace stone {
class Action;

class Step {
protected:
  const Action &source;

public:
  Step(const Action &source);

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

} // namespace stone
#endif
