#ifndef STONE_DRIVER_DRIVEROPTIONS_H
#define STONE_DRIVER_DRIVEROPTIONS_H

#include "stone/Session/SessionOptions.h"

namespace stone {
class DriverOptions final : public SessionOptions {
public:
  DriverOptions(LangOptions &langOpts) : SessionOptions(langOpts) {}

public:
};
} // namespace stone

#endif