#ifndef STONE_DRIVER_EVENT_H
#define STONE_DRIVER_EVENT_H

#include "stone/Core/List.h"
#include "stone/Driver/LinkType.h"
#include "stone/Session/FileType.h"

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

namespace Stone {
namespace Driver {
class Event {
  unsigned kind : 4;
  unsigned ty : 28;

public:
  using size_type = llvm::ArrayRef<const Event *>::size_type;
  using iterator = llvm::ArrayRef<const Event *>::iterator;
  using const_iterator = llvm::ArrayRef<const Event *>::const_iterator;

  enum class Kind : unsigned {
    Input = 0,
    Compile,
    Backend,
    DynamicLink,
    StaticLink,
    Assemble,
    First = Compile,
    Last = Assemble
  };
  Event(Event::Kind kind, file::FileType ty) : kind(unsigned(kind)), ty(ty) {}
  virtual ~Event() = default;

public:
  Event::Kind GetKind() const { return static_cast<Event::Kind>(kind); }
  file::FileType GetType() const { return static_cast<file::FileType>(ty); }
  const char *GetName(Event::Kind kind);

private:
  /// Events must be created through Compilation::CreateEvent.
  void *operator new(size_t size) { return ::operator new(size); };
};

// An event that represents and input file
class InputEvent : public Event {
  const llvm::opt::Arg &input;

public:
  InputEvent(const llvm::opt::Arg &intput, file::FileType ty)
      : Event(Event::Kind::Input, ty), input(input) {}

  const llvm::opt::Arg &GetInput() const { return input; }

  static bool classof(const Event *e) {
    return e->GetKind() == Event::Kind::Input;
  }
};

class InputProfile {};

class CompilationEvent : public Event {
  bool async = false;
  // A list of user events
  llvm::TinyPtrVector<const Event *> inputs;

public:
  CompilationEvent(Event::Kind kind, llvm::ArrayRef<const Event *> inputs,
                   file::FileType ty, InputProfile inputProfile)
      : Event(kind, ty), inputs(inputs) {}
  bool IsAsync() { return async; }

public:
  llvm::ArrayRef<const Event *> GetInputs() const { return inputs; }
  void AddInput(const Event *input) { inputs.push_back(input); }

  size_type Size() const { return inputs.size(); }

  iterator begin() { return inputs.begin(); }
  iterator end() { return inputs.end(); }
  const_iterator begin() const { return inputs.begin(); }
  const_iterator end() const { return inputs.end(); }

  // Returns the index of the Input action's output file which is used as
  // (single) input to this action. Most actions produce only a single output
  // file, so we return 0 by default.
  virtual size_t GetInputIndex() const { return 0; }

  static bool classof(const Event *e) {
    return (e->GetKind() >= Kind::First && e->GetKind() <= Kind::Last);
  }
};

class CompileEvent final : public CompilationEvent {
public:
  CompileEvent(file::FileType outputType)
      : CompilationEvent(Event::Kind::Compile, llvm::None, outputType, {}) {}

  CompileEvent(Event *input, file::FileType outputType,
               InputProfile inputProfile)
      : CompilationEvent(Event::Kind::Compile, input, outputType,
                         inputProfile) {}

  static bool classof(const Event *e) {
    return e->GetKind() == Event::Kind::Compile;
  }

  /// Return a *single* FileType::Stone InputEvent, if one exists;
  /// if 0 or >1 such inputs exist, return nullptr.
  const InputEvent *FindSingleInput(file::FileType ty) const {
    auto inputs = GetInputs();
    const InputEvent *e = nullptr;
    for (auto const *input : inputs) {
      if (auto const *s = dyn_cast<InputEvent>(input)) {
        if (s->GetType() == ty) {
          if (e == nullptr) {
            e = s;
          } else {
            // Already found one, two is too many.
            return nullptr;
          }
        }
      }
    }
    return e;
  }
};
class BackendEvent final : public CompilationEvent {
private:
  // In case of multi-threaded compilation, the compile-event produces multiple
  // output bitcode-files. For each bitcode-file a BackendEvent is created.
  // This index specifies which of the files to select for the input.
  size_t inputIndex;

public:
  BackendEvent(const Event *input, file::FileType outputType, size_t inputIndex)
      : CompilationEvent(Event::Kind::Backend, input, outputType, {}),
        inputIndex(inputIndex) {}

  static bool classof(const Event *e) {
    return e->GetKind() == Event::Kind::Backend;
  }
  virtual size_t GetInputIndex() const override { return inputIndex; }
};

class DynamicLinkEvent final : public CompilationEvent {
  LinkType linkType;
  bool shouldPerformLTO;

public:
  DynamicLinkEvent(llvm::ArrayRef<const Event *> inputs, LinkType linkType,
                   bool shouldPerformLTO)
      : CompilationEvent(Event::Kind::DynamicLink, inputs,
                         file::FileType::Image, {}),
        linkType(linkType), shouldPerformLTO(shouldPerformLTO) {

    assert(linkType != LinkType::None && linkType != LinkType::StaticLibrary);
  }

  LinkType GetLinkType() const { return linkType; }
  bool ShouldPerformLTO() const { return shouldPerformLTO; }

  static bool classof(const Event *e) {
    return e->GetKind() == Event::Kind::DynamicLink;
  }
};

class StaticLinkEvent : public CompilationEvent {
  LinkType linkType;

public:
  StaticLinkEvent(ArrayRef<const Event *> inputs, LinkType linkType)
      : CompilationEvent(Event::Kind::StaticLink, inputs, file::FileType::Image,
                         {}),
        linkType(linkType) {
    assert(linkType == LinkType::StaticLibrary);
  }
  static bool classof(const Event *e) {
    return e->GetKind() == Event::Kind::StaticLink;
  }
};

class AssembleEvent final : public CompilationEvent {

public:
  AssembleEvent(const Event *input, file::FileType outputType)
      : CompilationEvent(Event::Kind::Assemble, input, outputType, {}) {}

  static bool classof(const Event *e) {
    return e->GetKind() == Event::Kind::Assemble;
  }
};

class EventList final : public List<Event> {
public:
  void Print() const;
};
} // namespace Driver
} // namespace Stone
#endif
