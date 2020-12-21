#include "stone/Analyze/Lexer.h"

using namespace stone;

uint32_t stone::ValidateUTF8Char(const char *&startOfByte, const char *end) {

  return 0;
}

static bool IsNewLine(const char ch) {
  switch (ch) {
  case '\n':
  case '\r':
    return true;
  default:
    return false;
  }
}

static bool IsWhiteSpace(const char ch) {
  switch (ch) {
  case ' ':
  case '\t':
  case '\f':
  case '\v':
    return true;
  default:
    return false;
  }
}
static bool IsOperator(const char ch) {
  switch (ch) {
  case '=':
  case '-':
  case '+':
  case '*':
  case '&':
  case '|':
  case '^':
  case '~':
  case '.':
    return true;
  default:
    return false;
  }
}
static bool IsNumber(const char ch) {
  switch (ch) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    return true;
  default:
    return false;
  }
}
static bool IsIdentifier(const char ch) {
  switch (ch) {
  case 'A':
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
  case 'G':
  case 'H':
  case 'I':
  case 'J':
  case 'K':
  case 'L':
  case 'M':
  case 'N':
  case 'O':
  case 'P':
  case 'Q':
  case 'R':
  case 'S':
  case 'T':
  case 'U':
  case 'V':
  case 'W':
  case 'X':
  case 'Y':
  case 'Z':
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
  case 'i':
  case 'j':
  case 'k':
  case 'l':
  case 'm':
  case 'n':
  case 'o':
  case 'p':
  case 'q':
  case 'r':
  case 's':
  case 't':
  case 'u':
  case 'v':
  case 'w':
  case 'x':
  case 'y':
  case 'z':
  case '_':
    return true;
  default:
    return false;
  }
}

Lexer::Lexer(const FileID srcID, SrcMgr &sm, const LangOptions &lo,
             DiagnosticEngine *de)
    : srcID(srcID), sm(sm), lo(lo), de(de) {}

// Init();

void Lexer::Init(const char *bufferStart, const char *curPtr,
                 const char *bufferEnd) {}

void Lexer::Lex(Token &token) {

  while (true) {
  }
}

void Lexer::LexTrivia(Trivia) {}
void Lexer::LexChar() {}

void Lexer::LexNumber() {}

void Lexer::LexStrLiteral() {}
