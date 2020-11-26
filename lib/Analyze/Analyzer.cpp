#include "stone/Analyze/Analyzer.h"
#include "stone/Core/Ret.h"

#include "stone/Analyze/Analysis.h"
#include "stone/Analyze/Check.h"
#include "stone/Analyze/Parse.h"

using namespace stone;

Analyzer::Analyzer(Analysis& analysis) : analysis(analysis) {

}

int Analyzer::Analyze(Pipeline* P) {
	
	//stone::Parse(AS, P); 

	//stone::Check(AS, P); 


	return ret::ok; 
}
