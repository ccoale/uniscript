#ifndef _METHODDECLARATION_H
#define _METHODDECLARATION_H
#include "VariableDeclaration.h"

namespace Uniscript
{
	class MethodDeclaration
	{
	private:
		// The attributes of this method (public, private, etc.)
		int attr;

		// The name of the Method (e.g. "add")
		std::string name;

		// The type of the Method (e.g. "int")
		std::string type;

		// The queue of parameters (e.g. "<int> x, <int> y")
		std::queue<VariableDeclaration> params;
	public:
		// Creates a new instance of a MethodDeclaration.
		// type - the return type of the Method
		// name - the name of the Method
		// params - the queue of parameters of the Method
		MethodDeclaration(const std::string &type, const std::string &name, const std::queue<VariableDeclaration> params);
	};
}

#endif /* _METHODDECLARATION_H */