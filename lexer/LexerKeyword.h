#ifndef _LEXERKEYWORD_H
#define _LEXERKEYWORD_H
#include <iostream>
#include <string>

namespace Uniscript
{
	struct LexerKeywordInfo
	{
		LexerKeywordInfo(unsigned int _id, std::string _name)
		{
			id = _id;
			name = _name;
		}

		LexerKeywordInfo()
		{
			id = 0;
			name = "";
		}

		// the id of the keyword
		unsigned int id;

		// the name of the keyword
		std::string name;
	};
}

#endif /* _LEXERKEYWORD_H */