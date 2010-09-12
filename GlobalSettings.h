#ifndef _GLOBALSETTINGS_H
#define _GLOBALSETTINGS_H
#include <iostream>
#include <string>

namespace Uniscript
{
	// This data structure stores information about global
	// settings of Uniscript, such as code and library paths.
	struct GlobalSettings
	{
		// The maximum number of recursive includes
		// a source may have. The default value is
		// 256.
		unsigned int maxIncludeDepth;

		// The default path for pre-compiled libraries
		// to be imported by sources. The default is
		// "./lib" (in a directory called "lib" child
		// to the current directory).
		std::string importPath;
	};
}

#endif /* _GLOBALSETTINGS_H */