#ifndef STONE_COMPILE_COMPILEOPTIONS_H
#define STONE_COMPILE_COMPILEOPTIONS_H

#include "stone/Compile/AnalysisOptions.h"
#include "stone/Compile/GenOptions.h"
#include "stone/Core/FileSystemOptions.h"
#include "stone/Core/SearchPathOptions.h"

#include "stone/Session/SessionOptions.h"

namespace Stone {
namespace Frontend {
class CompileOptions final : public SessionOptions {
public:
  GenOptions genOpts;
  AnalysisOptions analysisOpts;
  SearchPathOptions spOpts;
  FileSystemOptions fsOpts;

public:
  CompileOptions() {}
};
} // namespace Frontend
} // namespace Stone
#endif
