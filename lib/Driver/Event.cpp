#include "stone/Driver/Event.h"

using namespace Stone;

const char *Event::GetName(Event::Kind k) {
  switch (k) {
  case Event::Kind::Input:
    return "input";
  case Event::Kind::Compile:
    return "compile";
  case Event::Kind::Backend:
    return "backend";
  case Event::Kind::Assemble:
    return "assemble";
  case Event::Kind::DynamicLink:
    return "dynamic-link";
  case Event::Kind::StaticLink:
    return "static-link";
  }
  llvm_unreachable("invalid class");
}
