#ifndef _CLASSDECLARATION_H
#define _CLASSDECLARATION_H
#include "VariableDeclaration.h"

namespace Uniscript
{
	class ClassDeclaration
	{
	private:
		// The name of the class (e.g. "Console")
		std::string name;

	public:
		// Creates a new instance of a ClassDeclaration.
		// name - the name of the class
		ClassDeclaration(const std::string &name);
	};
}

#endif /* _FUNCTIONDECLARATION_H */