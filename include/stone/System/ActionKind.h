#ifndef STONE_SYSTEM_ACTIONKIND_H
#define STONE_SYSTEM_ACTIONKIND_H

#include "llvm/ADT/StringRef.h"

namespace {
enum { ACTION_ENABLED = 0x1, ACTION_DISABLED = 0x2, ACTION_FUTURE = 0x4 };
}
namespace stone {
enum class ActionKind {
#define ACTION(N) N,
#include "stone/System/ActionKind.def"
  MAX
};
/// If a token kind has determined text, return the text; otherwise assert.
llvm::StringRef GetActionText(ActionKind kind);
} // namespace stone
#endif
