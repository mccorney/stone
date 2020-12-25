#ifndef STONE_SYSTEM_ACTION_H
#define STONE_SYSTEM_ACTION_H

#include "stone/Core/LangOptions.h"
#include "stone/Core/Stats.h"
#include "stone/System/ActionKind.h"

#include "llvm/ADT/DenseMapInfo.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Allocator.h"
#include "llvm/Support/PointerLikeTypeTraits.h"
#include "llvm/Support/type_traits.h"

namespace stone {

enum { ActionAlignment = 8 };

class alignas(ActionAlignment) Action {
  friend class ActionTable;
  ActionKind kind;
  llvm::StringMapEntry<Action *> *entry = nullptr;

  unsigned chosen : 1;

public:
  ActionKind GetKind() { return kind; }
};

class ActionTable;
class ActionTableStats final : public Stats {
  const ActionTable &table;

public:
  ActionTableStats(const ActionTable &table) : table(table) {}
  void Print() const override;
};

class ActionTable final {
  const LangOptions &langOpts;
  friend ActionTableStats;
  using Entries = llvm::StringMap<Action *, llvm::BumpPtrAllocator>;
  Entries entries;

public:
  /// Create the action table, populating it with info about the
  /// language actions for the language specified by \p LangOpts.
  explicit ActionTable(const LangOptions &langOpts);

  llvm::BumpPtrAllocator &GetAllocator() { return entries.getAllocator(); }

  /// Return the action token info for the specified named
  /// action.
  Action &Get(llvm::StringRef name) {

    auto &entry = *entries.insert(std::make_pair(name, nullptr)).first;
    Action *&action = entry.second;
    if (action) {
      return *action;
    }
    // Lookups failed, make a new Action.
    void *mem = GetAllocator().Allocate<Action>();
    action = new (mem) Action();

    // Make sure GetName() knows how to find the Action
    // contents.
    action->entry = &entry;
    return *action;
  }

  Action &Get(llvm::StringRef name, ActionKind k) {
    auto &action = Get(name);
    action.kind = k;
    assert(action.kind == k && "ActionKind too large");
    return action;
  }

  /// Gets an Action for the given name without consulting
  ///        external sources.
  ///
  /// This is a version of Get() meant for external sources that want to
  /// introduce or modify an action. If they called Get(), they would
  /// likely end up in a recursion.
  Action &GetOwn(llvm::StringRef name) {

    auto &entry = *entries.insert(std::make_pair(name, nullptr)).first;
    Action *&action = entry.second;
    if (action) {
      action->chosen = true;
      return *action;
    }
    // Lookups failed, make a new Action.
    void *mem = GetAllocator().Allocate<Action>();
    action = new (mem) Action();

    // Make sure GetName() knows how to find the Action
    // contents.
    action->entry = &entry;
    return *action;
  }

  using iterator = Entries::const_iterator;
  using const_iterator = Entries::const_iterator;

  iterator begin() const { return entries.begin(); }
  iterator end() const { return entries.end(); }
  unsigned size() const { return entries.size(); }

  /// Populate the action table with info about the actions
  /// for the language specified by \p LangOpts.
  void AddActions(const LangOptions &LangOpts);
};

} // namespace stone
#endif
