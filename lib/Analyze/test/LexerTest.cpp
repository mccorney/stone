#include "stone/Analyze/Lexer.h"
#include "stone/Core/LangOptions.h"
#include "stone/Core/Mem.h"
#include "stone/Core/SrcMgr.h"

#include "gtest/gtest.h"

using namespace stone;

class LexerTest : public ::testing::Test {
protected:
  DiagnosticEngine de;
  DiagnosticOptions diagOpts;
  FileSystemOptions fmOpts;
  LangOptions langOpts;
  FileMgr fm;
  SrcMgr sm;
  // Lexer lexer;
protected:
  LexerTest() : de(diagOpts, nullptr, false), fm(fmOpts), sm(de, fm) {}

protected:
  std::unique_ptr<Lexer> CreateLexer(llvm::StringRef srcBuffer) {

    auto memBuffer = llvm::MemoryBuffer::getMemBuffer(srcBuffer);
    auto mainFileID = sm.CreateFileID(std::move(memBuffer));

    sm.SetMainFileID(mainFileID);
    auto lexer = llvm::make_unique<Lexer>(mainFileID, sm, langOpts /*de*/);
    return lexer;
  }
  std::vector<Token> Lex(llvm::StringRef srcBuffer) {

    auto lexer = CreateLexer(srcBuffer);
    std::vector<Token> tokens;
    while (true) {
      Token token;
      lexer->Lex(token);
      break;
    }
    return tokens;
  }
};

TEST_F(LexerTest, GetNextToken) {

  llvm::StringRef srcBuffer = "fun";

  auto tokens = Lex(srcBuffer);
}
