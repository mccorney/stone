#include "stone/Analyze/Analyzer.h"
#include "stone/Core/Ret.h"

#include "stone/Analyze/Analysis.h"


using namespace stone;

Analyzer::Analyzer(Analysis& AS) : AS(AS) {

}

int Analyzer::Analyze(Pipeline* P) {
	return ret::ok; 
}
