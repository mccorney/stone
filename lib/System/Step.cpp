#include "stone/System/Step.h"
#include "stone/System/Action.h"

using namespace stone;

Step::Step(StepKind kind, const Action &source) : kind(kind), source(source) {}

SyncStep::SyncStep(StepKind kind, const Action &source) : Step(kind, source) {}

AsyncStep::AsyncStep(StepKind kind, const Action &source)
    : Step(kind, source) {}

CompileStep::CompileStep(const Action &source)
    : AsyncStep(StepKind::Compile, source) {}

AssembleStep::AssembleStep(const Action &source)
    : AsyncStep(StepKind::Assemble, source) {}

BackendStep::BackendStep(const Action &source)
    : AsyncStep(StepKind::Backend, source) {}

StaticLinkStep::StaticLinkStep(const Action &source)
    : AsyncStep(StepKind::StaticLink, source) {}

DynamicLinkStep::DynamicLinkStep(const Action &source)
    : AsyncStep(StepKind::DynamicLink, source) {}
