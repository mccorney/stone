//===- SrcLoc.cpp - Compact identifier for Source Files -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
//  This file defines accessor methods for the FullSourceLoc class.
//
//===----------------------------------------------------------------------===//

#include "stone/Core/SrcLoc.h"
#include "stone/Core/LLVM.h"
//#include "stone/Core/PrettyStackTrace.h"
#include "stone/Core/SrcMgr.h"



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
// SrcLoc
//===----------------------------------------------------------------------===//

void SrcLoc::print(raw_ostream &OS, const SrcMgr &SM)const{
  if (!isValid()) {
    OS << "<invalid loc>";
    return;
  }

  if (isFileID()) {
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
  if (Loc.isFileID()) {

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
// FullSourceLoc
//===----------------------------------------------------------------------===//

FileID FullSourceLoc::getFileID() const {
  assert(isValid());
  return srcMgr->getFileID(*this);
}

FullSourceLoc FullSourceLoc::getExpansionLoc() const {
  assert(isValid());
  return FullSourceLoc(srcMgr->getExpansionLoc(*this), *srcMgr);
}

FullSourceLoc FullSourceLoc::getSpellingLoc() const {
  assert(isValid());
  return FullSourceLoc(srcMgr->getSpellingLoc(*this), *srcMgr);
}

FullSourceLoc FullSourceLoc::getFileLoc() const {
  assert(isValid());
  return FullSourceLoc(srcMgr->getFileLoc(*this), *srcMgr);
}

PresumedLoc FullSourceLoc::getPresumedLoc(bool UseLineDirectives) const {
  if (!isValid())
    return PresumedLoc();

  return srcMgr->getPresumedLoc(*this, UseLineDirectives);
}

bool FullSourceLoc::isMacroArgExpansion(FullSourceLoc *StartLoc) const {
  assert(isValid());
  return srcMgr->isMacroArgExpansion(*this, StartLoc);
}

FullSourceLoc FullSourceLoc::getImmediateMacroCallerLoc() const {
  assert(isValid());
  return FullSourceLoc(srcMgr->getImmediateMacroCallerLoc(*this), *srcMgr);
}

std::pair<FullSourceLoc, StringRef> FullSourceLoc::getModuleImportLoc() const {
  if (!isValid())
    return std::make_pair(FullSourceLoc(), StringRef());

  std::pair<SrcLoc, StringRef> ImportLoc =
      srcMgr->getModuleImportLoc(*this);
  return std::make_pair(FullSourceLoc(ImportLoc.first, *srcMgr),
                        ImportLoc.second);
}

unsigned FullSourceLoc::getFileOffset() const {
  assert(isValid());
  return srcMgr->getFileOffset(*this);
}

unsigned FullSourceLoc::getLineNumber(bool *Invalid) const {
  assert(isValid());
  return srcMgr->getLineNumber(getFileID(), getFileOffset(), Invalid);
}

unsigned FullSourceLoc::getColumnNumber(bool *Invalid) const {
  assert(isValid());
  return srcMgr->getColumnNumber(getFileID(), getFileOffset(), Invalid);
}

const SrcFile *FullSourceLoc::getSrcFile() const {
  assert(isValid());
  return srcMgr->getSrcFileForID(getFileID());
}

unsigned FullSourceLoc::getExpansionLineNumber(bool *Invalid) const {
  assert(isValid());
  return srcMgr->getExpansionLineNumber(*this, Invalid);
}

unsigned FullSourceLoc::getExpansionColumnNumber(bool *Invalid) const {
  assert(isValid());
  return srcMgr->getExpansionColumnNumber(*this, Invalid);
}

unsigned FullSourceLoc::getSpellingLineNumber(bool *Invalid) const {
  assert(isValid());
  return srcMgr->getSpellingLineNumber(*this, Invalid);
}

unsigned FullSourceLoc::getSpellingColumnNumber(bool *Invalid) const {
  assert(isValid());
  return srcMgr->getSpellingColumnNumber(*this, Invalid);
}

bool FullSourceLoc::isInSystemHeader() const {
  assert(isValid());
  return srcMgr->isInSystemHeader(*this);
}

bool FullSourceLoc::isBeforeInTranslationUnitThan(SrcLoc Loc) const {
  assert(isValid());
  return srcMgr->isBeforeInTranslationUnit(*this, Loc);
}

LLVM_DUMP_METHOD void FullSourceLoc::dump() const {
  SrcLoc::dump(*srcMgr);
}

const char *FullSourceLoc::getCharacterData(bool *Invalid) const {
  assert(isValid());
  return srcMgr->getCharacterData(*this, Invalid);
}

StringRef FullSourceLoc::getBufferData(bool *Invalid) const {
  assert(isValid());
  return srcMgr->getBuffer(srcMgr->getFileID(*this), Invalid)->getBuffer();
}

std::pair<FileID, unsigned> FullSourceLoc::getDecomposedLoc() const {
  return srcMgr->getDecomposedLoc(*this);
}
