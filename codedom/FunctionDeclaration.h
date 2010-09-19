#ifndef _FUNCTIONDECLARATION_H
#define _FUNCTIONDECLARATION_H
#include "VariableDeclaration.h"

namespace Uniscript
{
	class FunctionDeclaration
	{
	private:
		// The name of the function (e.g. "add")
		std::string name;

		// The type of the function (e.g. "int")
		std::string type;

		// The queue of parameters (e.g. "<int> x, <int> y")
		std::queue<VariableDeclaration> params;
	public:
		// Creates a new instance of a FunctionDeclaration.
		// type - the return type of the function
		// name - the name of the function
		// params - the queue of parameters of the function
		FunctionDeclaration(const std::string &type, const std::string &name, const std::queue<VariableDeclaration> params);
	};
}

#endif /* _FUNCTIONDECLARATION_H */