#ifndef STONE_SYSTEM_HELP_H
#define STONE_SYSTEM_HELP_H

namespace stone {

	enum class HelpMode { 
		Compile,
		System
	};
	int Help(HelpMode Mode);
}

#endif 
