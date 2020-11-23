#ifndef STONE_ANALYZE_LEXER_H
#define STONE_ANALYZE_LEXER_H

#include "stone/Core/SrcLoc.h"

namespace stone {

class SrcID;
class SrcMgr; 
class Token;
class LangOptions;
class Token;
class DiagEngine;

class Lexer final {
	SrcID ID; 
	DiagEngine* DE = nullptr;

	const char *StartBuff; 
	const char *CurPtr; 
	const char *EndBuff;

	private:
		void Init(const char *StartBuff, const char *CurPtr, const char *EndBuff); 
	public:
		Lexer(const SrcID ID, const SrcMgr& SM, const LangOptions& LO, DiagEngine* DG = nullptr);
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

