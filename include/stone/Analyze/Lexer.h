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
	SrcID ID; 
	Diag* DG = nullptr;

	const char *StartBuff; 
	const char *CurPtr; 
	const char *EndBuff;

	private:
		void Init(const char *StartBuff, const char *CurPtr, const char *EndBuff); 
	public:
		Lexer(const SrcID ID, const SrcMgr& SM, const LangOptions& LO, Diag* DG = nullptr);
	public:
		void Lex(Token& T);
	public:	
		void LexIdentifier();
		void LexNumber();
		void LexStrLiteral(); 
		void LexChar();
	public:
};

}
#endif 

