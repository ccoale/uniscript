#ifndef _EXPRESSION_H
#define _EXPRESSION_H
#include "../Lexer/LexerToken.h"
#include <queue>

namespace Uniscript
{
	class Expression
	{
	private:
		// The tokens that belong to this expression.
		std::queue<LexerToken> tokens;

		// Whether or not this expression is primitive.
		bool isPrimitive;
	public:
		// Creates a new instance of an expression.
		// toks -- a queue of tokens to be evaluated.
		// isPrim -- whether or not the toks queue contains a single primitive expression (i.e. a number, string, char, etc.)
		Expression(const std::queue<LexerToken> &toks, bool isPrim = false);
	};
}

#endif /* _VARIABLEDECLARATION_H */