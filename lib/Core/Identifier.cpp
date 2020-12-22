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

/// Returns true if the identifier is a keyword
bool Identifier::IsKeyword(const LangOptions &langOpts) const {

  /*
switch (getTokenKwStatus(LangOpts, getTokenID())) {
case KS_Enabled:
case KS_Extension:
return true;
default:
return false;
}
  */

  return false;
}

IdentifierTable::IdentifierTable(const LangOptions &langOpts)
    : langOpts(langOpts) {
  // Populate the identifier table with info
  // about keywords for the current language.
  //
  // TODO: AddKeywords(LangOpts);
}

/*
/// Translates flags as specified in TokenKinds.def into keyword status
/// in the given language standard.
static KeywordStatus getKeywordStatus(const LangOptions &LangOpts,
                                      unsigned Flags) {
  if (Flags == KEYALL)
    return KS_Enabled;
  if (LangOpts.CPlusPlus && (Flags & KEYCXX))
    return KS_Enabled;
  if (LangOpts.CPlusPlus11 && (Flags & KEYCXX11))
    return KS_Enabled;
  if (LangOpts.CPlusPlus2a && (Flags & KEYCXX2A))
    return KS_Enabled;
  if (LangOpts.C99 && (Flags & KEYC99))
    return KS_Enabled;
  if (LangOpts.GNUKeywords && (Flags & KEYGNU))
    return KS_Extension;
  if (LangOpts.MicrosoftExt && (Flags & KEYMS))
    return KS_Extension;
  if (LangOpts.MSVCCompat && (Flags & KEYMSCOMPAT))
    return KS_Enabled;
  if (LangOpts.Borland && (Flags & KEYBORLAND))
    return KS_Extension;
  if (LangOpts.Bool && (Flags & BOOLSUPPORT))
    return KS_Enabled;
  if (LangOpts.Half && (Flags & HALFSUPPORT))
    return KS_Enabled;
  if (LangOpts.WChar && (Flags & WCHARSUPPORT))
    return KS_Enabled;
  if (LangOpts.Char8 && (Flags & CHAR8SUPPORT))
    return KS_Enabled;
  if (LangOpts.AltiVec && (Flags & KEYALTIVEC))
    return KS_Enabled;
  if (LangOpts.ZVector && (Flags & KEYZVECTOR))
    return KS_Enabled;
  if (LangOpts.OpenCL && !LangOpts.OpenCLCPlusPlus && (Flags & KEYOPENCLC))
    return KS_Enabled;
  if (LangOpts.OpenCLCPlusPlus && (Flags & KEYOPENCLCXX))
    return KS_Enabled;
  if (!LangOpts.CPlusPlus && (Flags & KEYNOCXX))
    return KS_Enabled;
  if (LangOpts.C11 && (Flags & KEYC11))
    return KS_Enabled;
  // We treat bridge casts as objective-C keywords so we can warn on them
  // in non-arc mode.
  if (LangOpts.ObjC && (Flags & KEYOBJC))
    return KS_Enabled;
  if (LangOpts.ConceptsTS && (Flags & KEYCONCEPTS))
    return KS_Enabled;
  if (LangOpts.Coroutines && (Flags & KEYCOROUTINES))
    return KS_Enabled;
  if (LangOpts.ModulesTS && (Flags & KEYMODULES))
    return KS_Enabled;
  if (LangOpts.CPlusPlus && (Flags & KEYALLCXX))
    return KS_Future;
  return KS_Disabled;
}

/// AddKeyword - This method is used to associate a token ID with specific
/// identifiers because they are language keywords.  This causes the lexer to
/// automatically map matching identifiers to specialized token codes.
static void AddKeyword(StringRef Keyword, tok::TokenKind TokenCode,
                       unsigned Flags, const LangOptions &LangOpts,
                       IdentifierTable &Table) {
  KeywordStatus AddResult = getKeywordStatus(LangOpts, Flags);

  // Don't add this keyword under MSVCCompat.
  if (LangOpts.MSVCCompat && (Flags & KEYNOMS18) &&
      !LangOpts.isCompatibleWithMSVC(LangOptions::MSVC2015))
    return;

  // Don't add this keyword under OpenCL.
  if (LangOpts.OpenCL && (Flags & KEYNOOPENCL))
    return;

  // Don't add this keyword if disabled in this language.
  if (AddResult == KS_Disabled)
    return;

  Identifier &Info =
      Table.get(Keyword, AddResult == KS_Future ? tok::identifier : TokenCode);

  Info.setIsExtensionToken(AddResult == KS_Extension);
  Info.setIsFutureCompatKeyword(AddResult == KS_Future);
}

/// AddCXXOperatorKeyword - Register a C++ operator keyword alternative
/// representations.
static void AddOperatorKeyword(StringRef Keyword, tok::TokenKind TokenCode,
                               IdentifierTable &Table) {

  Identifier &Info = Table.get(Keyword, TokenCode);
  Info.setIsOperatorKeyword();
}
*/

/*
/// AddKeywords - Add all keywords to the symbol table.
///
void IdentifierTable::AddKeywords(const LangOptions &LangOpts) {
  // Add keywords and tokens for the current language.
#define KEYWORD(NAME, FLAGS)                                                   \
  AddKeyword(StringRef(#NAME), tok::kw_##NAME, FLAGS, LangOpts, *this);
#define ALIAS(NAME, TOK, FLAGS)                                                \
  AddKeyword(StringRef(NAME), tok::kw_##TOK, FLAGS, LangOpts, *this);
#define CXX_KEYWORD_OPERATOR(NAME, ALIAS)                                      \
  if (LangOpts.CXXOperatorNames)                                               \
    AddCXXOperatorKeyword(StringRef(#NAME), tok::ALIAS, *this);
#define OBJC_AT_KEYWORD(NAME)                                                  \
  if (LangOpts.ObjC)                                                           \
    AddObjCKeyword(StringRef(#NAME), tok::objc_##NAME, *this);
#define TESTING_KEYWORD(NAME, FLAGS)
#include "stone/Core/TokenKinds.def"

  if (LangOpts.ParseUnknownAnytype)
    AddKeyword("__unknown_anytype", tok::kw___unknown_anytype, KEYALL, LangOpts,
               *this);

  if (LangOpts.DeclSpecKeyword)
    AddKeyword("__declspec", tok::kw___declspec, KEYALL, LangOpts, *this);

  // Add the 'import' contextual keyword.
  get("import").setModulesImport(true);
}
*/

/*
/// Checks if the specified token kind represents a keyword in the
/// specified language.
/// \returns Status of the keyword in the language.
static KeywordStatus getTokenKwStatus(const LangOptions &LangOpts,
                                      tok::TokenKind K) {
  switch (K) {
#define KEYWORD(NAME, FLAGS)                                                   \
  case tok::kw_##NAME:                                                         \
    return getKeywordStatus(LangOpts, FLAGS);
#include "stone/Core/TokenKinds.def"
  default:
    return KS_Disabled;
  }
}
*/

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
