#include "stone/Core/Identifier.h"
#include "stone/Core/Char.h"
#include "stone/Core/LangOptions.h"
//#include "stone/Core/OperatorKinds.h"
//#include "stone/Core/Specifiers.h"
#include "stone/Core/TokenKind.h"

#include "llvm/ADT/DenseMapInfo.h"
#include "llvm/ADT/FoldingSet.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Allocator.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>

using namespace stone;

enum class KeywordStatus {
  On,
  Off,
  Reserved,
};
static KeywordStatus GetKeywordStatus(const LangOptions &langOpts,
                                      unsigned flag) {
  if (flag & KEYON) {
    return KeywordStatus::On;
  }
  if (flag & KEYRSV) {
    return KeywordStatus::Reserved;
  }
  return KeywordStatus::Off;
}
/// Returns true if the identifier is a keyword
bool Identifier::IsKeyword(const LangOptions &langOpts) const {

	switch (kind) {
#define KEYWORD(NAME, FLAG)                                                   \
  case tk::kw_##NAME:                                                         \
    return GetKeywordStatus(langOpts, FLAG) == KeywordStatus::On;
#include "stone/Core/TokenKind.def"
  default:
    return false; 
  }
}

IdentifierTable::IdentifierTable(const LangOptions &langOpts)
    : langOpts(langOpts) {
  AddKeywords(langOpts);
}

static void AddKeyword(llvm::StringRef keyword, tk kind, unsigned flag,
                       const LangOptions &langOpts, IdentifierTable &table) {

  auto status = GetKeywordStatus(langOpts, flag);
  if (status == KeywordStatus::Off) {
    return;
  }
  auto &identifier =  table.Get(keyword, 
			status == KeywordStatus::Reserved ? tk::identifier : kind);

  identifier.SetIsKeywordReserved(status == KeywordStatus::Reserved);
}

void IdentifierTable::AddKeywords(const LangOptions &LangOpts) {
  // Add keywords and tokens for the current language.
#define KEYWORD(NAME, FLAG)                                                    \
  AddKeyword(llvm::StringRef(#NAME), tk::kw_##NAME, FLAG, langOpts, *this);
#include "stone/Core/TokenKind.def"
}


//===----------------------------------------------------------------------===//
// Stats Implementation
//===----------------------------------------------------------------------===//

/*
/// PrintStats - Print statistics about how well the identifier table is doing
/// at hashing identifiers.
void IdentifierTableStat::Print() const {
  unsigned NumBuckets = HashTable.getNumBuckets();
  unsigned NumIdentifiers = HashTable.getNumItems();
  unsigned NumEmptyBuckets = NumBuckets - NumIdentifiers;
  unsigned AverageIdentifierSize = 0;
  unsigned MaxIdentifierLength = 0;

  // TODO: Figure out maximum times an identifier had to probe for -stats.
  for (llvm::StringMap<Identifier *, llvm::BumpPtrAllocator>::const_iterator
           I = HashTable.begin(),
           E = HashTable.end();
       I != E; ++I) {
    unsigned IdLen = I->getKeyLength();
    AverageIdentifierSize += IdLen;
    if (MaxIdentifierLength < IdLen)
      MaxIdentifierLength = IdLen;
  }

  fprintf(stderr, "\n*** Identifier Table Stats:\n");
  fprintf(stderr, "# Identifiers:   %d\n", NumIdentifiers);
  fprintf(stderr, "# Empty Buckets: %d\n", NumEmptyBuckets);
  fprintf(stderr, "Hash density (#identifiers per bucket): %f\n",
          NumIdentifiers / (double)NumBuckets);
  fprintf(stderr, "Ave identifier length: %f\n",
          (AverageIdentifierSize / (double)NumIdentifiers));
  fprintf(stderr, "Max identifier length: %d\n", MaxIdentifierLength);

  // Compute statistics about the memory allocated for identifiers.
  HashTable.getAllocator().PrintStats();
}

*/
