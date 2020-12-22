#include "stone/Core/ASTCtx.h"

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/Support/Allocator.h"
#include "llvm/Support/Compiler.h"
#include <algorithm>
#include <memory>

using namespace stone;

ASTCtx::ASTCtx(const LangOptions &langOpts,
               const SearchPathOptions &searchPathOpts, SrcMgr &sm)
    : langOpts(langOpts), searchPathOpts(searchPathOpts), sm(sm),
      identifiers(langOpts), stat(*this) {

  builtin.Init(*this);
}
Identifier &ASTCtx::GetIdentifier(llvm::StringRef name) {
  return identifiers.Get(name);
}
size_t ASTCtx::GetSizeOfMemUsed() const { return bumpAlloc.getTotalMemory(); }
