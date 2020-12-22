#ifndef STONE_ANALYZE_TOKENKINDS_H
#define STONE_ANALYZE_TOKENKINDS_H

#include "stone/Core/LLVM.h"

namespace {
enum { KEYON = 0x1, KEYOFF = 0x2, KEYRSV = 0x4 };
}
namespace stone {

enum class tk {
#define TOKEN(X) X,
#include "stone/Core/TokenKind.def"
  MAX
};

/// Check whether a token kind is known to have any specific text content.
/// e.g., tol::l_paren has determined text however tok::identifier doesn't.
bool IsTokenTextDetermined(tk kind);

/// If a token kind has determined text, return the text; otherwise assert.
llvm::StringRef GetTokenText(tk kind);

void DumpTokenKind(llvm::raw_ostream &os, tk kind);
} // namespace stone

#endif
