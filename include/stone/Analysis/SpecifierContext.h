#ifndef STONE_ANALYSIS_PARSING_CONTEXT_H
#define STONE_ANALYSIS_PARSING_CONTEXT_H

#include "stone/Analysis/Analysis.h"
#include "stone/Analysis/AnalysisOptions.h"
#include "stone/Analysis/ParserDiagnostic.h"
#include "stone/Core/ASTContext.h"
#include "stone/Core/Module.h"
#include "stone/Core/Stats.h"

#include <memory>

namespace stone {

enum AccessLevel {
  /// Available to outside of the module and all levels within the module
  Public,
  /// Available only within the module
  Internal,
  /// Available on within the declaration
  Private
};

class ScopeSpecifier {};

class DeclSpecifier {};

class SpecifierContext final {};

} // namespace stone
#endif
