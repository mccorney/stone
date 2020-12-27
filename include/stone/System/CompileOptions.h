#ifndef STONE_SYSTEM_COMPILEOPTIONS_H
#define STONE_SYSTEM_COMPILEOPTIONS_H

#include "stone/Analysis/AnalysisOptions.h"
#include "stone/Gen/GenOptions.h"
#include "stone/System/SessionOptions.h"

namespace stone {

class CompileOptions final : public SessionOptions {
public:
  GenOptions genOpts;
  AnalysisOptions analyzeOpts;

public:
  CompileOptions(LangOptions &langOpts) : SessionOptions(langOpts) {}
};

} // namespace stone
#endif
