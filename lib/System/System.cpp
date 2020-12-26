#include "stone/System/System.h"
#include "stone/Core/Ret.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallSet.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/Config/llvm-config.h"
#include "llvm/Option/Arg.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Option/OptSpecifier.h"
#include "llvm/Option/OptTable.h"
#include "llvm/Option/Option.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/Process.h"
#include "llvm/Support/Program.h"
#include "llvm/Support/StringSaver.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/VirtualFileSystem.h"
#include "llvm/Support/raw_ostream.h"

using namespace stone;

System::System(llvm::StringRef stoneExecutable, llvm::StringRef targetTriple,
               llvm::IntrusiveRefCntPtr<llvm::vfs::FileSystem> vfs)
    : vfs(std::move(vfs)), stoneExecutablePath(stoneExecutablePath),
      /*sysRoot(DEFAULT_SYSROOT),*/
      driverTitle("Stone Compiler"), targetTriple(targetTriple),
      strSaver(bumpAlloc), checkInputFilesExist(true) {

  // Provide a sane fallback if no VFS is specified.
  if (!this->vfs)
    this->vfs = llvm::vfs::getRealFileSystem();
}

void System::Init(llvm::ArrayRef<const char *> Args) {}

int System::Run() { return ret::ok; }
