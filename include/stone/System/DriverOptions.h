#ifndef STONE_SYSTEM_SYSTEMOPTIONS_H
#define STONE_SYSTEM_SYSTEMOPTIONS_H

#include "stone/System/SessionOptions.h"

namespace stone {
class DriverOptions final : public SessionOptions {
public:
  DriverOptions(LangOptions &langOpts) : SessionOptions(langOpts) {}

public:
};
} // namespace stone

#endif
