#ifndef STONE_SYSTEM_EVENT_H
#define STONE_SYSTEM_EVENT_H

#include "llvm/ADT/DenseMapInfo.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Allocator.h"
#include "llvm/Support/PointerLikeTypeTraits.h"
#include "llvm/Support/type_traits.h"

namespace stone {

class Event {
public:
  enum class Kind { User, Compilation };
};

// There can only be one user event per compilation session.
class UserEvent : public Event {
  const llvm::opt::Arg *intput = nullptr;

public:
  enum class Kind {
    Parse,
    Check,
    EmitIR,
    EmitBC,
    EmitExecutable,
    EmitObject,
    EmitAssembly
  };

public:
  UserEvent(const llvm::opt::Arg *intput, file::FileType ft)
      : Event(Event::Kind::User) {}
};

class CompilationEvent : public Event {
  // List of user events
public:
  enum class Kind {
    Compile,
    Backend,
    DynamicLink,
    StaticLink,
    Assemble,
    First = Compile,
    Last = Assemble
  };

public:
  CompilationEvent() : Event(Event::Kind::Compilation) {}
};

class CompileEvent : public CompilationEvent {};
class BackendEvent : public CompilationEvent {};

} // namespace stone
#endif
