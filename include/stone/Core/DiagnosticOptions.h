#ifndef STONE_CORE_DIAGNOSTICOPTIONS_H
#define STONE_CORE_DIAGNOSTICOPTIONS_H

#include "llvm/ADT/Hashing.h"

namespace stone {

/// Options for controlling diagnostics.
struct DiagnosticOptions final {
public:
  /// Indicates whether textual diagnostics should use color.
  bool UseColor = false;

  enum FormattingStyle { LLVM, Stone };
  // If set to true, use the more descriptive experimental formatting style for
  // diagnostics.
  FormattingStyle TextFormattingStyle = FormattingStyle::LLVM;
};

} // namespace stone

#endif
