#ifndef STONE_SYSTEM_BASICOPTIONS_H
#define STONE_SYSTEM_BASICOPTIONS_H

#include "stone/System/Action.h"
#include "stone/System/Options.h"

namespace stone {

class BasicOptions {
  Action *action = nullptr;
  ActionTable actions;
  std::unique_ptr<llvm::opt::OptTable> optTable;

public:
  LangOptions langOpts;
  BasicOptions() : actions(langOpts), optTable(stone::CreateOptTable()) {}

public:
  Action *GetAction() {
    assert(action && "No action");
    return action;
  }
  llvm::opt::OptTable &GetOptTable() const { return *optTable.get(); }
};
} // namespace stone

#endif
