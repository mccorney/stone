#include "stone/System/Action.h"

using namespace stone;

enum class ActionStatus {
  Enabled,
  Disabled,
  Future,
};
static ActionStatus GetActionStatus(const LangOptions &langOpts,
                                    unsigned flag) {
  if (flag & ACTION_ENABLED) {
    return ActionStatus::Enabled;
  }
  if (flag & ACTION_FUTURE) {
    return ActionStatus::Future;
  }
  return ActionStatus::Disabled;
}
/*
/// Returns true if the identifier is a keyword
bool Action::IsAction(const LangOptions &langOpts) const {


    switch (kind) {
  #define COMPILE_ACTION(NAME, FLAG) \
    case tk::kw_##NAME: \ return GetActionStatus(langOpts, FLAG) ==
  ActionStatus::On; #include "stone/Core/TokenKind.def" default: return false;
    }

  return true;
}
*/

static void AddAction(ActionKind kind, llvm::StringRef name, unsigned flag,
                      const LangOptions &langOpts, ActionTable &actions) {
  auto status = GetActionStatus(langOpts, flag);
  if (status == ActionStatus::Disabled) {
    return;
  }
  auto &action = actions.Get(
      name, status == ActionStatus::Future ? ActionKind::None : kind);

  // action.SetIsActionFuture(status == ActionStatus::Future);
}
ActionTable::ActionTable(const LangOptions &langOpts) : langOpts(langOpts) {
  AddActions(langOpts);
}
void ActionTable::AddActions(const LangOptions &LangOpts) {

#define COMPILE_ACTION(KIND, NAME, FLAG)                                       \
  AddAction(ActionKind::KIND, llvm::StringRef(NAME), FLAG, langOpts, *this);
#include "stone/System/ActionKind.def"
}

void ActionTableStats::Print() const {}
