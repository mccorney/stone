#ifndef STONE_COMPILE_COMPILEUNIT_H
#define STONE_COMPILE_COMPILEUNIT_H

#include "stone/Compile/AnalysisOptions.h"
#include "stone/Compile/GenOptions.h"
#include "stone/Core/FileSystemOptions.h"
#include "stone/Core/SearchPathOptions.h"
#include "stone/Core/SrcLoc.h"
#include "stone/Session/SessionOptions.h"

#include "llvm/ADT/ArrayRef.h"

namespace stone {
namespace analysis {
class SourceUnit;
class CompileUnit final {
  SourceUnit &su;
  OutputFile *outputFile = nullptr;
  CompileScope *scope = nullptr;
  Compiler &compiler;
public:
  enum class Stage { Parsed, Checked };

public:
  CompileUnit(SourceUnit &su, Compiler &compiler);
};
} // namespace analysis
} // namespace stone
#endif
