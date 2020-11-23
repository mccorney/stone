#ifndef STONE_CORE_FILESYSTEM_H
#define STONE_CORE_FILESYSTEM_H

#include <string>

namespace stone{

struct FileSystemOptions final {
	std::string WorkingDir;
};

class FileSystemStatCache final {
	std::string WorkingDir;
};


}

#endif


