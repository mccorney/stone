#ifndef STONE_SYSTEM_HELP_H
#define STONE_SYSTEM_HELP_H

namespace stone {

enum class HelpMode { Compiler, Driver };
int Help(HelpMode Mode);
} // namespace stone

#endif
