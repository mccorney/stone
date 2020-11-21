#ifndef STONE_ANALYSIS_LEXER_H
#define STONE_ANALYSIS_LEXER_H

class SrcMgr; 
class Token; 

class Lexer final {
	private:
		void Init(); 
	public:
		Lexer(int SrcID, SrcMgr* SM);
	public:
		void Lex(Token& Tk); 
};

#endif 

