#include "lexer/CodeLexer.h"
#include <iostream>

int main()
{
	std::vector<Uniscript::LexerToken> toks;
	std::vector<Uniscript::LexerErrorInfo> errs;

	std::cout << Uniscript::CodeLexer::LexSource("+ + += ++ - -= -- / /= * *= ** **= % %= = == ( ) [ ] { } 'A' 'B' 'c' 'D''e'",
		0, "", NULL, &toks, &errs);

	for (int i = 0; i < toks.size(); i++) {
		std::cout << toks[i].type;
		if (toks[i].type == (TOK_CHAR)) std::cout << toks[i].n8;
		std::cout << "\n";
	}
}