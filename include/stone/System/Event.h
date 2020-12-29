#ifndef STONE_SYSTEM_EVENT_H
#define STONE_SYSTEM_EVENT_H

#include "stone/Core/List.h"
#include "stone/System/FileType.h"

#include "llvm/ADT/DenseMapInfo.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Allocator.h"
#include "llvm/Support/PointerLikeTypeTraits.h"
#include "llvm/Support/type_traits.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/ADT/TinyPtrVector.h"
#include "llvm/Support/Chrono.h"

namespace llvm {
namespace opt {
class Arg;
}
} // namespace llvm

namespace stone {
namespace driver {
class Event {
  unsigned kind : 4;
  unsigned ty : 28;

public:
  using size_type = llvm::ArrayRef<const Event *>::size_type;
  using iterator = llvm::ArrayRef<const Event *>::iterator;
  using const_iterator = llvm::ArrayRef<const Event *>::const_iterator;

  enum class Kind : unsigned {
    InputEvent = 0,
    CompileEvent,
    BackendEvent,
    DynamicLinkEvent,
    StaticLinkEvent,
    AssembleEvent,
    First = CompileEvent,
    Last = AssembleEvent
  };
  Event(Event::Kind kind, file::FileType ty) : kind(unsigned(kind)), ty(ty) {}

public:
  Event::Kind GetKind() const { return static_cast<Event::Kind>(kind); }
  file::FileType GetType() const { return static_cast<file::FileType>(ty); }

private:
  /// Actions must be created through Compilation::CreateEvent.
  void *operator new(size_t size) { return ::operator new(size); };
};

// An event that represents and input file
class InputEvent : public Event {
  const llvm::opt::Arg &input;

public:
  InputEvent(const llvm::opt::Arg &intput, file::FileType ty)
      : Event(Event::Kind::InputEvent, ty), input(input) {}

  const llvm::opt::Arg &GetInput() const { return input; }

  static bool classof(const Event *e) {
    return e->GetKind() == Event::Kind::InputEvent;
  }
};

class CompilationEvent : public Event {
  bool async = false;
  // A list of user events
  llvm::TinyPtrVector<const Event *> inputs;

public:
  CompilationEvent(Event::Kind kind, llvm::ArrayRef<const Event *> inputs,
                   file::FileType ty)
      : Event(kind, ty), inputs(inputs) {}

  bool IsAsync() { return async; }
};

// class CompileEvent : public CompilationEvent {};

// class BackendEvent : public CompilationEvent {};

// class DynamicLinkEvent : public CompilationEvent {};

// class StaticLinkEvent : public CompilationEvent {};

// class AssembleEvent : public CompilationEvent {};

class EventList final : public List<Event> {
public:
  void Print() const;
};

} // namespace driver
} // namespace stone
#endif
