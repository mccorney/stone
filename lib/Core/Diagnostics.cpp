#include "stone/Core/Diagnostics.h"

#include <memory>

using namespace stone;

DiagnosticEngine::DiagnosticEngine(const DiagnosticOptions &diagOpts,
                                   DiagnosticListener *listener,
                                   bool ownsListener) {}

DiagnosticEngine::~DiagnosticEngine() {}

void DiagnosticEngine::AddDiagnostic(std::unique_ptr<Diagnostic> diagnostic) {

  // diagnostic->diagnosticID  = de.size() + 1;
  // diagnostics.insert(diagnostic->diagnosticID, std::move(diagnostic));
}
