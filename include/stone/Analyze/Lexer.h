#ifndef STONE_ANALYZE_LEXER_H
#define STONE_ANALYZE_LEXER_H

#include "stone/Analyze/LexerDiagnostic.h"
#include "stone/Analyze/Token.h"
#include "stone/Analyze/Trivia.h"

#include "stone/Core/SrcLoc.h"

namespace stone {

class SrcID;
class SrcMgr;
class Token;
class LangOptions;
class Token;
class Diag;


enum class TriviaRetentionMode {
  Without,
  With,
};

/// Given a pointer to the starting byte of a UTF8 character, validate it and
/// advance the lexer past it.  This returns the encoded character or ~0U if
/// the encoding is invalid.
uint32_t ValidateUTF8Char(const char *&startOfByte, const char *end);

class Lexer final {

  FileID srcID;
  DiagnosticEngine *de = nullptr;
  SrcMgr &sm;
  const LangOptions &lo;

  // LexerDiagnostic lexDiag;

  // const char *bufferStart;
  // const char *curPtr;
  // const char *bufferEnd;

  /// Pointer to the first character of the buffer, even in a lexer that
  /// scans a subrange of the buffer.
  const char *bufferStart;

  /// Pointer to one past the end character of the buffer, even in a lexer
  /// that scans a subrange of the buffer.  Because the buffer is always
  /// NUL-terminated, this points to the NUL terminator.
  const char *bufferEnd;

  /// Pointer to the artificial EOF that is located before BufferEnd.  Useful
  /// for lexing subranges of a buffer.
  const char *artificialEOF = nullptr;

  /// If non-null, points to the '\0' character in the buffer where we should
  /// produce a code completion token.
  const char *codeCompletionPtr = nullptr;

  /// Points to BufferStart or past the end of UTF-8 BOM sequence if it exists.
  const char *contentStart;

  /// Pointer to the next not consumed character.
  const char *curPtr;

  Token nextToken;

  /// The current leading trivia for the next token.
  ///
  /// This is only preserved if this Lexer was constructed with
  /// `TriviaRetentionMode::With`.
  Trivia leadingTrivia;

  /// The current trailing trivia for the next token.
  ///
  /// This is only preserved if this Lexer was constructed with
  /// `TriviaRetentionMode::With`.
  Trivia trailingTrivia;

public:
  // Making this public for now
  TriviaRetentionMode triviaRetention;

private:
  Lexer(const Lexer &) = delete;
  void operator=(const Lexer &) = delete;

  void Init(const char *bufferStart, const char *curPtr, const char *bufferEnd);

public:
  Lexer(const FileID srcID, SrcMgr &sm, const LangOptions &lo,
        DiagnosticEngine *de = nullptr);

public:
  void Lex(Token &token);

private:
  void LexTrivia(Trivia trivia);

  void LexIdentifier();
  void LexNumber();
  void LexStrLiteral();
  void LexChar();

public:
};

} // namespace stone
#endif
