#ifndef STONE_CORE_DIAGNOSTICS_H
#define STONE_CORE_DIAGNOSTICS_H

#include "stone/Core/DiagnosticOptions.h"
#include "stone/Core/SrcLoc.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/iterator_range.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Error.h"

#include <cassert>
#include <cstdint>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace stone {
class DiagnosticBuilder;

class FixIt final {};

class DiagnosticPrinter {};
class DiagnosticListener {};

class Diagnostic {
  // bool isActive;
protected:
  unsigned diagnosticID = 0;
  unsigned startPos = 0;
  unsigned endPos = 0;

public:
  const unsigned GetID() { return diagnosticID; }
  const unsigned GetStartPos() { return startPos; }
  const unsigned GetEndPos() { return endPos; }

public:
};

enum class DiagnosticLevel {
  None,
  Ignore,
  Note,
  Remark,
  Warning,
  Error,
  Fatal
};

enum class DiagnositicArgument {
  /// std::string
  STDString,

  /// const char *
  CString,

  /// int
  SInt,

  /// unsigned
  UInt,
};
/// Concrete class used by the front-end to report problems and issues.
///
/// This massages the diagnostics (e.g. handling things like "report warnings
/// as errors" and passes them off to the DiagnosticConsumer for reporting to
/// the user. Diagnostics is tied to one translation unit and one
/// SrcMgr.
class Diagnostics final {
public:
  Diagnostics(const DiagnosticOptions &diagOpts,
              DiagnosticListener *listener = nullptr, bool ownsListener = true);

  Diagnostics(const Diagnostics &) = delete;
  Diagnostics &operator=(const Diagnostics &) = delete;
  ~Diagnostics();

public:
  /// Owns the Diagnostic
  // void AddDiagnostic(std::unique_ptr<Diagnostic> diagnostic);

  // void AddDiagnosticListener(std::unique_ptr<DiagnosticListener> diagnostic);
};

class DiagnosticBuilder final {

  friend class Diagnostics;
  // friend class PartialDiagnostic;

  mutable Diagnostics *diagnostics = nullptr;
  mutable unsigned numArgs = 0;

  /// Status variable indicating if this diagnostic is still active.
  ///
  // NOTE: This field is redundant with DiagObj (IsActive iff (DiagObj == 0)),
  // but LLVM is not currently smart enough to eliminate the null check that
  // Emit() would end up with if we used that as our status variable.
  mutable bool isActive = false;

  /// Flag indicating that this diagnostic is being emitted via a
  /// call to ForceEmit.
  mutable bool isForceEmit = false;

  DiagnosticBuilder() = default;

  explicit DiagnosticBuilder(Diagnostics *diagnostics)
      : diagnostics(diagnostics), isActive(true) {

    assert(diagnostics &&
           "DiagnosticBuilder requires a valid DiagnosticsEngine!");

    // diagnostics->diagnosticRanges.clear();
    // diagnostics->diagnosticFixIts.clear();
  }

public:
  /// Issue the message to the client.
  ///
  /// This actually returns an instance of DiagnosticBuilder which emits the
  /// diagnostics (through @c ProcessDiag) when it is destroyed.
  ///
  /// \param DiagID A member of the @c diag::kind enum.
  /// \param Loc Represents the source location associated with the diagnostic,
  /// which can be an invalid location if no position information is available.
  inline DiagnosticBuilder Diagnose(SrcLoc loc, const unsigned diagnosticID,
                                    const unsigned messageID);

  inline DiagnosticBuilder Diagnose(const unsigned diagnosticID,
                                    const unsigned messageID);
};

} // namespace stone
#endif
