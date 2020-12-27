#ifndef STONE_CORE_CONTEXT_H
#define STONE_CORE_CONTEXT_H

#include "stone/Core/DiagnosticOptions.h"
#include "stone/Core/Diagnostics.h"
#include "stone/Core/LangOptions.h"

namespace stone {
class Context {
protected:
  LangOptions langOpts;
  DiagnosticOptions diagOpts;
  llvm::raw_ostream &os;
  DiagnosticEngine diagEngine;

public:
  Context();

public:
  llvm::raw_ostream &Out() { return os; }
  DiagnosticEngine &GetDiagEngine() { return diagEngine; }
  LangOptions &GetLangOptions() { return langOpts; }
};

} // namespace stone
#endif
