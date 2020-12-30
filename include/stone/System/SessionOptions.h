#ifndef STONE_SYSTEM_SESSIONOPTIONS_H
#define STONE_SYSTEM_SESSIONOPTIONS_H

#include "stone/Core/LangOptions.h"
#include "stone/System/Options.h"

namespace stone {

class SessionOptions {
  std::unique_ptr<llvm::opt::OptTable> optTable;
public:
  bool showHelp = false;
  bool showLifecycle = false;
public:
  SessionOptions(LangOptions &langOpts) : optTable(stone::CreateOptTable()) {}
public:
	llvm::opt::OptTable &GetOpts() const { return *optTable.get(); }
};
} // namespace stone

#endif
