#ifndef STONE_SYSTEM_COMPILEOPTIONS_H
#define STONE_SYSTEM_COMPILEOPTIONS_H

#include "stone/Analyze/AnalyzeOptions.h"
#include "stone/Gen/GenOptions.h"
#include "stone/System/BasicOptions.h"

namespace stone {

class CompileOptions final : public BasicOptions {
public:
  GenOptions genOpts;
  AnalyzeOptions analyzeOpts;
};

} // namespace stone
#endif
