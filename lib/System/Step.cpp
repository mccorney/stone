#include "stone/System/Step.h"
#include "stone/System/Action.h"

using namespace stone;

Step::Step(const Action &source) : source(source) {}

SyncStep::SyncStep(const Action &source) : Step(source) {}

AsyncStep::AsyncStep(const Action &source) : Step(source) {}

CompileStep::CompileStep(const Action &source) : AsyncStep(source) {}

LinkStep::LinkStep(const Action &source) : AsyncStep(source) {}

AssembleStep::AssembleStep(const Action &source) : AsyncStep(source) {}

BackendStep::BackendStep(const Action &source) : AsyncStep(source) {}
