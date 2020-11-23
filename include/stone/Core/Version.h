#ifndef STONE_CORE_VERSION_H
#define STONE_CORE_VERSION_H

namespace stone {
  /// Retrieves the repository path (e.g., Subversion path) that
  /// identifies the particular Stone branch, tag, or trunk from which this
  /// Stone was built.
  std::string GetRepoPath();

  /// Retrieves the repository path from which LLVM was built.
  ///
  /// This supports LLVM residing in a separate repository from stone.
  std::string GetLLVMRepoPath();

  /// Retrieves the repository revision number (or identifier) from which
  /// this Stone was built.
  std::string GetRevision();

  /// Retrieves the repository revision number (or identifier) from which
  /// LLVM was built.
  ///
  /// If Stone and LLVM are in the same repository, this returns the same
  /// string as GetRevision.
  std::string GetLLVMRevision();

  /// Retrieves the full repository version that is an amalgamation of
  /// the information in GetRepPath() and GetRevision().
  std::string GetFullRepoVersion();

  /// Retrieves a string representing the complete stone version,
  /// which includes the stone version number, the repository version,
  /// and the vendor tag.
  std::string GetFullVersion();

  /// Like GeFullVersion(), but with a custom tool name.
  //std::string GetToolFullVersion(llvm::StringRef ToolName);
 }

#endif
