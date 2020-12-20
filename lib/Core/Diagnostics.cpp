#include "stone/Core/Diagnostics.h"

#include <memory>

using namespace stone;

void DiagnosticEngine::AddDiagnostic(std::unique_ptr<Diagnostic> diagnostic) {

  // diagnostic->diagnosticID  = de.size() + 1;
  // diagnostics.insert(diagnostic->diagnosticID, std::move(diagnostic));
}
