#ifndef _VARIABLEDECLARATION_H
#define _VARIABLEDECLARATION_H
#include "../Lexer/LexerToken.h"
#include "Expression.h"
#include <queue>

namespace Uniscript
{
	class VariableDeclaration
	{
	private:
		// The type of the variable.
		std::string type;

		// The name of the variable.
		std::string name;

		// The initial value of the variable (can be empty).
		Expression initValue;
	public:
		// Creates a new instance of this VariableDeclaration.
		// type - the type of the variable (e.g. "string", "int", "long", "short", "char", etc.)
		// name - the name of the variable (e.g. "myVariable", "helloWorld", etc.)
		// exp - the expression for the initialization of this variable.
		VariableDeclaration(const std::string &type, const std::string &name, const Expression &exp);
	};
}

#endif /* _VARIABLEDECLARATION_H */