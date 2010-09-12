#include "lexer/CodeLexer.h"
#include <iostream>

int main()
{
	std::vector<Uniscript::LexerToken> toks;
	std::vector<Uniscript::LexerErrorInfo> errs;

	/*std::cout <<*/ Uniscript::CodeLexer::LexSource("0xFFFFF",
		0, "", NULL, &toks, &errs);

	for (int i = 0; i < toks.size(); i++) {
		std::cout << toks[i].type << "\n";
		if (toks[i].type == (TOK_STR)) std::cout << ">>> " << toks[i].str << "\n";
		else if (toks[i].type == (TOK_CHAR)) std::cout << ">>> " << toks[i].n8 << "\n";
		else if (toks[i].type == (TOK_FLOAT)) std::cout << ">>> float: " << toks[i].f32 << "\n";
		else if (toks[i].type == (TOK_DOUBLE)) std::cout << ">>> double: " << toks[i].f64 << "\n";
		else if (toks[i].type == (TOK_SHORT)) std::cout << ">>> short: " << toks[i].n16 << "\n";
	}
}