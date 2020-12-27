#include "stone/Core/ASTContext.h"

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/Support/Allocator.h"
#include "llvm/Support/Compiler.h"
#include <algorithm>
#include <memory>

using namespace stone;

ASTContext::ASTContext(Context &context, const SearchPathOptions &spOpts,
                       SrcMgr &sm)
    : context(context), searchPathOpts(spOpts), sm(sm),
      identifiers(context.GetLangOptions()), stats(*this) {

  builtin.Init(*this);
}
Identifier &ASTContext::GetIdentifier(llvm::StringRef name) {
  return identifiers.Get(name);
}
size_t ASTContext::GetSizeOfMemUsed() const {
  return bumpAlloc.getTotalMemory();
}

void ASTContextStats::Print() const {}
