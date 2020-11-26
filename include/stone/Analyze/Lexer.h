#ifndef STONE_ANALYZE_LEXER_H
#define STONE_ANALYZE_LEXER_H

#include "stone/Core/SrcLoc.h"
#include "stone/Core/Diag.h"

namespace stone {

class SrcID;
class SrcMgr; 
class Token;
class LangOptions;
class Token;
class Diag;

class LexerDiagClient final : public DiagClient {
		public:
		unsigned int GetID() {
			if(ID == 0) {
				// Load
			}
			return ID; 
		}
};


class Lexer final {
	SrcID srcID; 
	Diag* dg = nullptr;

	const char *bufferStart; 
	const char *curPtr; 
	const char *bufferEnd;

	private:
		void Init(const char *bufferStart, const char *curPtr, const char *bufferEnd); 
	public:
		Lexer(const SrcID srcID, const SrcMgr& srcMgr, const LangOptions& langOpts, Diag* dg = nullptr);
	public:
		void Lex(Token& token);
	public:	
		void LexIdentifier();
		void LexNumber();
		void LexStrLiteral(); 
		void LexChar();
	public:
};

}
#endif 
