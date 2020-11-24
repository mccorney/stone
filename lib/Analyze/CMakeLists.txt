
set(stone_analyze_sources
	Analysis.cpp
	Analyze.cpp
	Analyzer.cpp
	Check.cpp
	Checker.cpp
	Lexer.cpp
	LexerTest.cpp
	Parse.cpp
	Parser.cpp
	ParserTest.cpp
	Token.cpp

	LINK_LIBS
	StoneCore
)
add_stone_library(StoneAnalyze
	${stone_analyze_sources}
)



