#include "stone/System/System.h"
#include "stone/Core/Ret.h"

using namespace stone;

System::System() {}

void System::Init(llvm::ArrayRef<const char *> Args) {}
int System::Run() { return ret::ok; }
