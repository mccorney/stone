#include "stone/Analyze/Token.h"

#include "llvm/ADT/StringRef.h"

using namespace stone;

bool stone::IsTokenTextDetermined(tk kind) { return false; }

llvm::StringRef stone::GetTokenText(tk kind) { return ""; }

void stone::DumpTokenKind(llvm::raw_ostream &os, tk kind) {}
