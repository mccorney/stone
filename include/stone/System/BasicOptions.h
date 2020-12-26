#ifndef STONE_SYSTEM_BASICOPTIONS_H
#define STONE_SYSTEM_BASICOPTIONS_H

#include "stone/System/Action.h"
#include "stone/System/Options.h"

namespace stone {

class BasicOptions {
  ActionTable actions;
	std::unique_ptr<llvm::opt::OptTable> optTable; 
public:
  LangOptions langOpts;
  BasicOptions() : actions(langOpts), optTable(stone::CreateOptTable()) {}
public:
  Action *GetAction() { return nullptr; }
	llvm::opt::OptTable& GetOptTable() { return *optTable.get(); }
};
} // namespace stone

#endif
