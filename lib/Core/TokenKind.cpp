#include "stone/Core/TokenKind.h"

#include "llvm/ADT/StringRef.h"

using namespace Stone;

bool Stone::IsTokenTextDetermined(tk kind) { return false; }

llvm::StringRef Stone::GetTokenText(tk kind) { return ""; }

void Stone::DumpTokenKind(llvm::raw_ostream &os, tk kind) {}
