#include "lexer/CodeLexer.h"
#include <iostream>

int main()
{
	std::vector<Uniscript::LexerToken> toks;
	std::vector<Uniscript::LexerErrorInfo> errs;

	std::cout << Uniscript::CodeLexer::LexSource("\"Hello World\"\"This is a test of a longer string to see if it will still work properly.\"",
		0, "", NULL, &toks, &errs);

	for (int i = 0; i < toks.size(); i++) {
		std::cout << toks[i].type << "\n";
		if (toks[i].type == (TOK_STR)) std::cout << ">>> " << toks[i].str << "\n";
		else if (toks[i].type == (TOK_CHAR)) std::cout << ">>> " << toks[i].n8 << "\n";
	}
}