#ifndef STONE_SYSTEM_SESSIONOPTIONS_H
#define STONE_SYSTEM_SESSIONOPTIONS_H

#include "stone/Core/LangOptions.h"
#include "stone/System/Action.h"
#include "stone/System/Options.h"

namespace stone {

class SessionOptions {
  std::unique_ptr<llvm::opt::OptTable> optTable;

protected:
  Action *action = nullptr;

public:
  bool showHelp = false;
  bool showCycle = false;
  ActionTable actions;

public:
  SessionOptions(LangOptions &langOpts)
      : actions(langOpts), optTable(stone::CreateOptTable()) {}

public:
  Action *GetAction() {
    assert(action && "No action");
    return action;
  }
  llvm::opt::OptTable &GetOptTable() const { return *optTable.get(); }
  ActionTable &GetActionTable() { return actions; }
};
} // namespace stone

#endif
