#include "stone/Driver/Event.h"

using namespace stone;

const char *Event::GetName(Event::Kind k) {
  switch (k) {
  case Event::Kind::Input:
    return "input";
  case Event::Kind::Compile:
    return "compiler";
  case Event::Kind::Backend:
    return "backend";
  case Event::Kind::Assemble:
    return "assembler";
  case Event::Kind::DynamicLink:
    return "dynamic-linker";
  case Event::Kind::StaticLink:
    return "static-linker";
  }
  llvm_unreachable("invalid class");
}
