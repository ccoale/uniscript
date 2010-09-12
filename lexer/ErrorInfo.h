#ifndef ERRORINFO_H
#define ERRORINFO_H
#include <iostream>
#include <string>

namespace Uniscript
{
	// This data structure provides information relating
	// to a lexical analysis error.
	struct LexerErrorInfo
	{
		LexerErrorInfo(unsigned int _line, unsigned int _col, unsigned int _id, std::string _error, std::string _file)
		{
			line = _line;
			col = _col;
			id = _id;
			error = _error;
			file = _file;
		}

		// The line number the error occurred on.
		unsigned int line;

		// The column number the error occured in.
		unsigned int col;

		// The actual error id.
		unsigned int id;

		// The error string.
		std::string error;

		// The file that this error occurred in.
		std::string file;
	};

	// No error.
	#define LEXERR_OK			0x00

	// The lexer could not open the specified file.
	#define LEXERR_NOFILE		0x01

	// Undefined character in character literal (e.g. 'a', 'b'. but.. ''' fails).
	#define LEXERR_UNEXPTOKINCHARLITERAL	0x02

	// The string literal has no closing quote.
	#define LEXERR_STRLITNOEND				0x03

	// Unexpected character in number literal
	#define LEXERR_UNEXPCHARINNUMLITERAL	0x04
}

#endif /* ERRORINFO_H */