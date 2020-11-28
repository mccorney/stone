#ifndef STONE_ANALYZE_LEXER_H
#define STONE_ANALYZE_LEXER_H

#include "stone/Analyze/LexerDiagnostic.h"
#include "stone/Core/SrcLoc.h"

namespace stone {

class SrcID;
class SrcMgr;
class Token;
class LangOptions;
class Token;
class Diag;

class Lexer final {
  FileID srcID;
  Diagnostics *dg = nullptr;
  // LexerDiagnostic lexDiag;

  const char *bufferStart;
  const char *curPtr;
  const char *bufferEnd;

private:
  void Init(const char *bufferStart, const char *curPtr, const char *bufferEnd);

public:
  Lexer(const FileID srcID, const SrcMgr &srcMgr, const LangOptions &langOpts,
        Diagnostics *dg = nullptr);

public:
  void Lex(Token &token);

public:
  void LexIdentifier();
  void LexNumber();
  void LexStrLiteral();
  void LexChar();

public:
};

} // namespace stone
#endif
