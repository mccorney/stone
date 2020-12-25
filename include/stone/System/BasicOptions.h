#ifndef STONE_SYSTEM_BASICOPTIONS_H
#define STONE_SYSTEM_BASICOPTIONS_H

#include "stone/System/Action.h"

namespace stone {

class BasicOptions {
  ActionTable actions;

public:
  LangOptions langOpts;
  BasicOptions() : actions(langOpts) {}

public:
  Action *GetAction() { return nullptr; }
};
} // namespace stone

#endif
