#ifndef STONE_CORE_FILESYSTEM_H
#define STONE_CORE_FILESYSTEM_H

#include <string>

namespace stone{

struct FileSystemOptions final {
	std::string workingDir;
};

class FileSystemStatCache final {
	std::string workingDir;
};


}

#endif


