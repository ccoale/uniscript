#ifndef _FORSTATEMENT_H
#define _FORSTATEMENT_H
#include "Expression.h"
#include <queue>

namespace Uniscript
{
	class ForStatement
	{
	private:
		// The variable initialization of the for-loop (if it has a variable with no declare)
		AssignStatement init;

		// The variable declaration of the for-loop.
		VariableDeclaration initDecl;

	public:
		// Creates a new instance of a WhileStatement
		WhileStatement(const Expression &exp);
	};
}

#endif /* _WHILESTATEMENT_H */