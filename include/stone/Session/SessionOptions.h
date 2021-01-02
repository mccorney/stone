#ifndef STONE_SESSION_SESSIONOPTIONS_H
#define STONE_SESSION_SESSIONOPTIONS_H

#include "stone/Core/LangOptions.h"
#include "stone/Session/Options.h"

namespace Stone {

class SessionOptions {
  std::unique_ptr<llvm::opt::OptTable> optTable;

public:
  bool showHelp = false;
  bool showLifecycle = false;

public:
  SessionOptions() : optTable(Stone::CreateOptTable()) {}

public:
  llvm::opt::OptTable &GetOpts() const { return *optTable.get(); }
};
} // namespace Stone

#endif
