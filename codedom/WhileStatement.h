#ifndef _WHILESTATEMENT_H
#define _WHILESTATEMENT_H
#include "Expression.h"
#include <queue>

namespace Uniscript
{
	class WhileStatement
	{
	private:
		// The expression of the while-statement.
		Expression expr;

	public:
		// Creates a new instance of a WhileStatement
		WhileStatement(const Expression &exp);
	};
}

#endif /* _WHILESTATEMENT_H */