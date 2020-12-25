#ifndef STONE_SYSTEM_BASICOPTIONS_H
#define STONE_SYSTEM_BASICOPTIONS_H

#include "stone/System/ActionKind.h"

namespace stone {

struct BasicOptions {
  ActionKind actionKind;
  LangOptions langOpts;
};
} // namespace stone

#endif
