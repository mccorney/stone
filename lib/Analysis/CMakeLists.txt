
set(stone_analysis_sources
	Analysis.cpp
	Check.cpp
	Checker.cpp
	Lexer.cpp
	Parse.cpp
	Parser.cpp
	Semantics.cpp
	Token.cpp
)
add_stone_library(StoneAnalysis
	${stone_analysis_sources}
)



