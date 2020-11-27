#include "stone/Core/SrcLoc.h"
#include "stone/Core/LLVM.h"
#include "stone/Core/SrcMgr.h"
#include "stone/Core/SrcFile.h"

//#include "stone/Core/PrettyStackTrace.h"

#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/raw_ostream.h"
#include <cassert>
#include <string>
#include <utility>

using namespace stone;

//===----------------------------------------------------------------------===//
// PrettyStackTraceLoc
//===----------------------------------------------------------------------===//

/*
void PrettyStackTraceLoc::print(raw_ostream &OS) const {
  if (Loc.isValid()) {
    Loc.print(OS, SM);
    OS << ": ";
  }
  OS << Message << '\n';
}
*/


//===----------------------------------------------------------------------===//
// SrcLocation
//===----------------------------------------------------------------------===//

void SrcLoc::print(raw_ostream &OS, const SrcMgr &SM)const{
  if (!isValid()) {
    OS << "<invalid loc>";
    return;
  }

  if (isSrcID()) {
    PresumedLoc PLoc = SM.getPresumedLoc(*this);

    if (PLoc.isInvalid()) {
      OS << "<invalid>";
      return;
    }
    // The macro expansion and spelling pos is identical for file locs.
    OS << PLoc.getFilename() << ':' << PLoc.getLine()
       << ':' << PLoc.getColumn();
    return;
  }

  SM.getExpansionLoc(*this).print(OS, SM);

  OS << " <Spelling=";
  SM.getSpellingLoc(*this).print(OS, SM);
  OS << '>';
}

LLVM_DUMP_METHOD std::string
SrcLoc::printToString(const SrcMgr &SM) const {
  std::string S;
  llvm::raw_string_ostream OS(S);
  print(OS, SM);
  return OS.str();
}

LLVM_DUMP_METHOD void SrcLoc::dump(const SrcMgr &SM) const {
  print(llvm::errs(), SM);
  llvm::errs() << '\n';
}

LLVM_DUMP_METHOD void SrcRange::dump(const SrcMgr &SM) const {
  print(llvm::errs(), SM);
  llvm::errs() << '\n';
}

static PresumedLoc PrintDifference(raw_ostream &OS, const SrcMgr &SM,
                                   SrcLoc Loc, PresumedLoc Previous) {
  if (Loc.isSrcID()) {

    PresumedLoc PLoc = SM.getPresumedLoc(Loc);

    if (PLoc.isInvalid()) {
      OS << "<invalid sloc>";
      return Previous;
    }

    if (Previous.isInvalid() ||
        strcmp(PLoc.getFilename(), Previous.getFilename()) != 0) {
      OS << PLoc.getFilename() << ':' << PLoc.getLine() << ':'
         << PLoc.getColumn();
    } else if (Previous.isInvalid() || PLoc.getLine() != Previous.getLine()) {
      OS << "line" << ':' << PLoc.getLine() << ':' << PLoc.getColumn();
    } else {
      OS << "col" << ':' << PLoc.getColumn();
    }
    return PLoc;
  }
  auto PrintedLoc = PrintDifference(OS, SM, SM.getExpansionLoc(Loc), Previous);

  OS << " <Spelling=";
  PrintedLoc = PrintDifference(OS, SM, SM.getSpellingLoc(Loc), PrintedLoc);
  OS << '>';
  return PrintedLoc;
}

void SrcRange::print(raw_ostream &OS, const SrcMgr &SM) const {

  OS << '<';
  auto PrintedLoc = PrintDifference(OS, SM, B, {});
  if (B != E) {
    OS << ", ";
    PrintDifference(OS, SM, E, PrintedLoc);
  }
  OS << '>';
}

LLVM_DUMP_METHOD std::string
SrcRange::printToString(const SrcMgr &SM) const {
  std::string S;
  llvm::raw_string_ostream OS(S);
  print(OS, SM);
  return OS.str();
}

//===----------------------------------------------------------------------===//
// FullSrcLoc
//===----------------------------------------------------------------------===//

SrcID FullSrcLoc::getSrcID() const {
  assert(isValid());
  return SM->getSrcID(*this);
}

FullSrcLoc FullSrcLoc::getExpansionLoc() const {
  assert(isValid());
  return FullSrcLoc(SM->getExpansionLoc(*this), *SM);
}

FullSrcLoc FullSrcLoc::getSpellingLoc() const {
  assert(isValid());
  return FullSrcLoc(SM->getSpellingLoc(*this), *SM);
}

FullSrcLoc FullSrcLoc::getFileLoc() const {
  assert(isValid());
  return FullSrcLoc(SM->getFileLoc(*this), *SM);
}

PresumedLoc FullSrcLoc::getPresumedLoc(bool UseLineDirectives) const {
  if (!isValid())
    return PresumedLoc();

  return SM->getPresumedLoc(*this, UseLineDirectives);
}

std::pair<FullSrcLoc, StringRef> FullSrcLoc::getModuleImportLoc() const {
  if (!isValid())
    return std::make_pair(FullSrcLoc(), StringRef());

  std::pair<SrcLoc, StringRef> ImportLoc =
      SM->getModuleImportLoc(*this);
  return std::make_pair(FullSrcLoc(ImportLoc.first, *SM),
                        ImportLoc.second);
}

unsigned FullSrcLoc::getFileOffset() const {
  assert(isValid());
  return SM->getFileOffset(*this);
}

unsigned FullSrcLoc::getLineNumber(bool *Invalid) const {
  assert(isValid());
  return SM->getLineNumber(getSrcID(), getFileOffset(), Invalid);
}

unsigned FullSrcLoc::GetColNumber(bool *Invalid) const {
  assert(isValid());
  return SM->GetColNumber(getSrcID(), getFileOffset(), Invalid);
}

const SrcFile *FullSrcLoc::getSrcFile() const {
  assert(isValid());
  return SM->getSrcFileForID(getSrcID());
}

unsigned FullSrcLoc::getExpansionLineNumber(bool *Invalid) const {
  assert(isValid());
  return SM->getExpansionLineNumber(*this, Invalid);
}

unsigned FullSrcLoc::getExpansionColumnNumber(bool *Invalid) const {
  assert(isValid());
  return SM->getExpansionColumnNumber(*this, Invalid);
}

unsigned FullSrcLoc::getSpellingLineNumber(bool *Invalid) const {
  assert(isValid());
  return SM->getSpellingLineNumber(*this, Invalid);
}

unsigned FullSrcLoc::getSpellingColumnNumber(bool *Invalid) const {
  assert(isValid());
  return SM->getSpellingColumnNumber(*this, Invalid);
}

bool FullSrcLoc::isInSystemHeader() const {
  assert(isValid());
  return SM->isInSystemHeader(*this);
}

bool FullSrcLoc::isBeforeInTranslationUnitThan(SrcLoc Loc) const {
  assert(isValid());
  return SM->isBeforeInTranslationUnit(*this, Loc);
}

LLVM_DUMP_METHOD void FullSrcLoc::dump() const {
  SrcLoc::dump(*SM);
}

const char *FullSrcLoc::getCharacterData(bool *Invalid) const {
  assert(isValid());
  return SM->getCharacterData(*this, Invalid);
}

StringRef FullSrcLoc::getBufferData(bool *Invalid) const {
  assert(isValid());
  return SM->getBuffer(SM->getSrcID(*this), Invalid)->getBuffer();
}

std::pair<SrcID, unsigned> FullSrcLoc::getDecomposedLoc() const {
  return SM->getDecomposedLoc(*this);
}
