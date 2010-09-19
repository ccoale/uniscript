//#include "lexer/CodeLexer.h"
#include <iostream>

int blah(char buffer[])
{
	buffer++;
	return 0;
}

int main()
{
	char a[1024];
	a++;
	blah(a);
}