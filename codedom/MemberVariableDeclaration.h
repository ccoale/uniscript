#ifndef _MEMBERVARIABLEDECLARATION_H
#define _MEMBERVARIABLEDECLARATION_H
#include "../Lexer/LexerToken.h"
#include "Expression.h"
#include <queue>

namespace Uniscript
{
	class MemberVariableDeclaration
	{
	private:
		// The attribute of the variable.
		int attr;

		// The type of the variable.
		std::string type;

		// The name of the variable.
		std::string name;

		// The initial value of the variable (can be empty).
		Expression initValue;
	public:
		// Creates a new instance of this MemberVariableDeclaration.
		// type - the type of the variable (e.g. "string", "int", "long", "short", "char", etc.)
		// name - the name of the variable (e.g. "myVariable", "helloWorld", etc.)
		// exp - the expression for the initialization of this variable.
		MemberVariableDeclaration(const std::string &type, const std::string &name, const Expression &exp);
	};
}

#endif /* _MEMBERVARIABLEDECLARATION_H */