#ifndef STONE_SYSTEM_COMPILEOPTIONS_H
#define STONE_SYSTEM_COMPILEOPTIONS_H

#include "stone/Analyze/AnalyzeOptions.h"
#include "stone/Gen/GenOptions.h"
#include "stone/System/BasicOptions.h"

namespace stone {

struct CompileOptions final : public BasicOptions {
  GenOptions genOpts;
  AnalyzeOptions analyzeOpts;
};

} // namespace stone
#endif
