#ifndef _CODELEXER_H
#define _CODELEXER_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "LexerToken.h"
#include "../GlobalSettings.h"
#include "ErrorInfo.h"

namespace Uniscript
{
	// This class provides methods for performing a lexical analysis
	// on a Uniscript source. This lexer does NOT provide logical
	// checking of semantics. It also does not provide checking
	// to make sure the source truly is Uniscript. It simply
	// lexes Uniscipt tokens. An error occurs if any unknown token
	// is reached.
	class CodeLexer
	{
	public:
		// LexFile lexes the given file returning the list of extracted tokens and
		// a numeric return value (0 if successful). If it failed, the list of
		// errors (up until a fatal error) is returned as well.
		static unsigned int LexFile(std::string szPath, const GlobalSettings *settings, 
			std::vector<LexerToken> *tokens, std::vector<LexerErrorInfo> *errors);

		// LexSource lexes the given source code string returning the list of extracted
		// tokens and a numeric return value (0 if successful). If it failed, the list of 
		// errors (up until a fata error) is returned as well.
		// Set length to 0 if length is unknown.
		static unsigned int LexSource(std::string szSource, unsigned int length, std::string szOptFile, 
			const GlobalSettings *settings, std::vector<LexerToken> *tokens, std::vector<LexerErrorInfo> *errors);

		// initializes the keywords
		static void InitKeys();
	private:
		static std::map<std::string, unsigned int> keys;
	};
}

#endif /* _CODELEXER_H */