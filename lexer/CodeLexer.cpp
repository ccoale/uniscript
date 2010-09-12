#include "CodeLexer.h"

namespace Uniscript
{
	// LexFile lexes the given file returning the list of extracted tokens and
	// a numeric return value (0 if successful). If it failed, the list of
	// errors (up until a fatal error) is returned as well.
	unsigned int CodeLexer::LexFile(std::string szPath, const GlobalSettings *settings, 
		std::vector<LexerToken> *tokens, std::vector<LexerErrorInfo> *errors)
	{
		// try to open the file
		FILE *fp = NULL;
		errno_t err = fopen_s(&fp, szPath.c_str(), "r");
		if (! fp) {
			errors->push_back(LexerErrorInfo(0, 0, LEXERR_NOFILE, "Could not open the file '" + szPath + "'.", "<none>"));
			return LEXERR_NOFILE;
		}

		// put cursor at the EOF
		fseek(fp, 0, SEEK_END);

		// get the length of the file
		long len = ftell(fp);

		// allocate a string that will store the contents of the file
		char *src = new char[len + 1];
		fseek(fp, 0, SEEK_SET);
		fread(src, 1, len, fp);
		src[len] = 0;

		std::string s_src = src;
		delete[] src;
		fclose(fp);

		// call the lexer to lex the source
		return CodeLexer::LexSource(s_src, len, szPath, settings, tokens, errors);
	}

	// LexSource lexes the given source code string returning the list of extracted
	// tokens and a numeric return value (0 if successful). If it failed, the list of 
	// errors (up until a fata error) is returned as well.
	unsigned int CodeLexer::LexSource(std::string szSource, unsigned int length, std::string szOptFile, 
		const GlobalSettings *settings, std::vector<LexerToken> *tokens, std::vector<LexerErrorInfo> *errors)
	{
		// grab our source code
		const char *src = szSource.c_str();

		// if length is unknown, let's calculate it
		if (length == 0)
			length = strlen(src);

		unsigned int i = 0; // the current index in this source code

		// Do we have anything to actually lex?
		if (szSource.empty())
			return LEXERR_OK;

		// look-ahead 1, 2, 3 characters.
		char la1 = 0, la2 = 0, la3 = 0;

		// line and column positions
		unsigned int line = 0, col = 0;

		// whether or not we are in a comment
		bool bInComment = false;

		// temporary token variable
		LexerToken tok;

		// temporary buffer to store string literal (without quotes)
		char stringLiteral[4096]; // 4,096 is PLENTY for now.

		// whether or not we found a closing quote
		bool metQuote = false;

		// the start of the string literal
		unsigned int stringStart = 0;

		// whether or not the hexadecimal 0x has been found
		bool foundX = false;

		// whether or not the floating point . has been found
		bool foundDot = false;

		// loop through each character in the source
		for (; i < length; i++)
		{
			// read the la characters
			la1 = src[i];
			la2 = (i < (length - 1)) ? src[i + 1] : 0;
			la3 = (i < (length - 2)) ? src[i + 2] : 0;
			if (la1 == '/' && la2 == '/') {
				bInComment = true;
			}
			col++;

			// check for newline
			if ((la1 == '\r' && la1 == '\n') || (la1 == '\n'))
			{
				line++;
				col = 0;
				bInComment = false;
				continue; // move ahead
			}

			// skip if we are still in a comment
			if (bInComment)
				continue;

			// syntax switch
			switch(la1)
			{
			case '<':
				if (la2 == '=') {
					tokens->push_back(LexerToken(line, col, TOK_LTE, szOptFile)); // <=
					i++;
				} else if (la2 == '<') {
					if (la3 == '=') {
						tokens->push_back(LexerToken(line, col, TOK_BSLEQU, szOptFile)); // <<=
						i++;
					} else {
						tokens->push_back(LexerToken(line, col, TOK_BSL, szOptFile)); // <<
					}
					i++;
				} else {
					tokens->push_back(LexerToken(line, col, TOK_LT, szOptFile)); // <
				}
				break;

			case '>':
				if (la2 == '=') {
					tokens->push_back(LexerToken(line, col, TOK_GTE, szOptFile)); // >=
					i++;
				} else if (la2 == '>') {
					if (la3 == '=') {
						tokens->push_back(LexerToken(line, col, TOK_BSREQU, szOptFile)); // >>=
						i++;
					} else {
						tokens->push_back(LexerToken(line, col, TOK_BSR, szOptFile)); // >=
					}
					i++;
				} else {
					tokens->push_back(LexerToken(line, col, TOK_GT, szOptFile)); // >
				}
				break;

			case '=':
				if (la2 == '=') {
					tokens->push_back(LexerToken(line, col, TOK_EQU, szOptFile));
					i++;
				} else {
					tokens->push_back(LexerToken(line, col, TOK_ASSIGN, szOptFile));
				}
				break;

			case '!':
				if (la2 == '=') {
					tokens->push_back(LexerToken(line, col, TOK_NE, szOptFile));
					i++;
				} else {
					tokens->push_back(LexerToken(line, col, TOK_LNOT, szOptFile));
				}
				break;

			case '&':
				if (la2 == '&') {
					tokens->push_back(LexerToken(line, col, TOK_LAND, szOptFile)); // &&
					i++;
				} else {
					tokens->push_back(LexerToken(line, col, TOK_BAND, szOptFile)); // &
				}
				break;

			case '|':
				if (la2 == '|') {
					tokens->push_back(LexerToken(line, col, TOK_LOR, szOptFile)); // ||
					i++;
				} else if (la2 == '=') {
					tokens->push_back(LexerToken(line, col, TOK_BOREQU, szOptFile)); // |=
					i++;
				} else {
					tokens->push_back(LexerToken(line, col, TOK_BOR, szOptFile)); // |
				}
				break;

			case '^':
				if (la2 == '=') {
					tokens->push_back(LexerToken(line, col, TOK_BXOR, szOptFile)); // ^=
					i++;
				} else {
					tokens->push_back(LexerToken(line, col, TOK_BXOREQU, szOptFile)); // ^
				}
				break;

			case '~':
				if (la2 == '=') {
					tokens->push_back(LexerToken(line, col, TOK_BNE, szOptFile)); // ~=
					i++;
				} else {
					tokens->push_back(LexerToken(line, col, TOK_BNOT, szOptFile)); // ~
				}
				break;

			case '+':
				if (la2 == '+') {
					tokens->push_back(LexerToken(line, col, TOK_INC, szOptFile)); // ++
					i++;
				} else if (la2 == '=') {
					tokens->push_back(LexerToken(line, col, TOK_ADDEQU, szOptFile)); // +=
					i++;
				} else {
					tokens->push_back(LexerToken(line, col, TOK_ADD, szOptFile)); // +
				}
				break;

			case '-':
				if (la2 == '-') {
					tokens->push_back(LexerToken(line, col, TOK_DEC, szOptFile)); // --
					i++;
				} else if (la2 == '=') {
					tokens->push_back(LexerToken(line, col, TOK_SUBEQU, szOptFile)); // -=
					i++;
				} else {
					tokens->push_back(LexerToken(line, col, TOK_SUB, szOptFile)); // -
				}
				break;

			case '*':
				if (la2 == '*') {
					if (la3 == '=') {
						tokens->push_back(LexerToken(line, col, TOK_POWEQU, szOptFile)); // **=
						i++;
					} else {
						tokens->push_back(LexerToken(line, col, TOK_POW, szOptFile)); // **
					}

					i++;
				} else if (la2 == '=') {
					tokens->push_back(LexerToken(line, col, TOK_MULEQU, szOptFile)); // *=
					i++;
				} else {
					tokens->push_back(LexerToken(line, col, TOK_MUL, szOptFile)); // *
				}
				break;

			case '/':
				if (la2 == '=') {
					tokens->push_back(LexerToken(line, col, TOK_DIVEQU, szOptFile)); // /=
					i++;
				} else {
					tokens->push_back(LexerToken(line, col, TOK_DIV, szOptFile)); // /
				}
				break;

			case '%':
				if (la2 == '=') {
					tokens->push_back(LexerToken(line, col, TOK_MODEQU, szOptFile)); // %=
					i++;
				} else {
					tokens->push_back(LexerToken(line, col, TOK_MOD, szOptFile)); // %
				}
				break;

			case '{':
				tokens->push_back(LexerToken(line, col, TOK_LBRACE, szOptFile)); // {
				break;

			case '}':
				tokens->push_back(LexerToken(line, col, TOK_RBRACE, szOptFile)); // }
				break;

			case '[':
				tokens->push_back(LexerToken(line, col, TOK_LBRACK, szOptFile)); // [
				break;

			case ']':
				tokens->push_back(LexerToken(line, col, TOK_RBRACK, szOptFile)); // ]
				break;

			case '(':
				tokens->push_back(LexerToken(line, col, TOK_LPAREN, szOptFile)); // (
				break;

			case ')':
				tokens->push_back(LexerToken(line, col, TOK_RPAREN, szOptFile)); // )
				break;
				
			case ';':
				tokens->push_back(LexerToken(line, col, TOK_END, szOptFile)); // ;
				break;

			case '.':
				tokens->push_back(LexerToken(line, col, TOK_DOT, szOptFile)); // .
				break;
			
			case ',':
				tokens->push_back(LexerToken(line, col, TOK_COMMA, szOptFile)); // ,
				break;

				// a single character token
			case '\'':
				// la2 MUST be a single ASCII character
				// la3 MUST be a single closing quote
				if (la2 == '\'' && la3 == '\'') {
					errors->push_back(LexerErrorInfo(line, col, LEXERR_UNEXPTOKINCHARLITERAL, "Unexpected token in character literal.", szOptFile));
					return LEXERR_UNEXPTOKINCHARLITERAL;
				} else if (la3 != '\'') {
					errors->push_back(LexerErrorInfo(line, col, LEXERR_UNEXPTOKINCHARLITERAL, "Unexpected token in character literal. Did you mean to use double quotes?", szOptFile));
					return LEXERR_UNEXPTOKINCHARLITERAL;
				}

				tok = LexerToken(line, col, TOK_CHAR, szOptFile);
				tok.n8 = la2;
				tokens->push_back(tok);
				i++;
				i++;

				break;

			case '"':
				// we must loop through all characters, excluding \r, \n, and \r\n, until we reach the
				// closing quote.
				metQuote = false;
				stringStart = ++i;
				for (; i < length; i++)
				{
					if (src[i] == '"') {
						metQuote = true;
						break;
					}

					stringLiteral[i - stringStart] = src[i];
				}
				stringLiteral[i - stringStart] = 0; // end the string

				// our string literal doesn't end!
				if (! metQuote) {
					errors->push_back(LexerErrorInfo(line, col, LEXERR_STRLITNOEND, "The string literal has no closing quote.", szOptFile));
					return LEXERR_STRLITNOEND;
				}

				// we now have our string literal
				LexerToken strTok = LexerToken(line, col, TOK_STR, szOptFile);
				strTok.str = new char[i - stringStart];
				strcpy(strTok.str, stringLiteral);
				strTok.str[i - stringStart] = 0;
				tokens->push_back(strTok);

				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				stringStart = i; // this will be the start of our number
				for (; i < length; i++)
				{
					
				}
				break;
			};
		}

		return LEXERR_OK;
	}
}