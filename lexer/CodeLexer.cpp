#include "CodeLexer.h"
#include "LexerKeyword.h"
#include <float.h>
#include <limits.h>
#include <stdlib.h>
#include <map>

namespace Uniscript
{
	std::map<std::string, unsigned int> CodeLexer::keys;

	// initializes the keywords
	void CodeLexer::InitKeys()
	{
		// declare all of our language keywords
		keys["alias"] = TOK_ALIAS;
		keys["break"] = TOK_BREAK;
		keys["case"] = TOK_CASE;
		keys["class"] = TOK_CLASS;
		keys["const"] = TOK_CONST;
		keys["continue"] = TOK_CONTINUE;
		keys["default"] = TOK_DEFAULT;
		keys["delete"] = TOK_DELETE;
		keys["do"] = TOK_DO;
		keys["else"] = TOK_ELSE;
		keys["enum"] = TOK_ENUM;
		keys["false"] = TOK_FALSE;
		keys["finally"] = TOK_FINALLY;
		keys["for"] = TOK_FOR;
		keys["foreach"] = TOK_FOREACH;
		keys["in"] = TOK_IN;
		keys["new"] = TOK_NEW;
		keys["null"] = TOK_NULL;
		keys["private"] = TOK_PRIVATE;
		keys["protected"] = TOK_PROTECTED;
		keys["public"] = TOK_PUBLIC;
		keys["ref"] = TOK_REF;
		keys["return"] = TOK_RETURN;
		keys["struct"] = TOK_STRUCT;
		keys["switch"] = TOK_SWITCH;
		keys["this"] = TOK_THIS;
		keys["throw"] = TOK_THROW;
		keys["true"] = TOK_TRUE;
		keys["typeof"] = TOK_TYPEOF;
		keys["while"] = TOK_WHILE;
	}

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

		// lb1 is a look-back 1
		char lb1 = 0;

		// temporary 64-bit integer
		__int64 ntmp = 0;

		// ending string tmp
		char *tmpEnd = 0;

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

			if (la1 == ' ')
				continue; // skip past whitespace.

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
				tok = LexerToken(line, col, TOK_STR, szOptFile);
				tok.str = new char[i - stringStart];
				strcpy(tok.str, stringLiteral);
				tok.str[i - stringStart] = 0;
				tokens->push_back(tok);

				break;

				// we need to lex numbers HERE
				// -------------------------

			default:
				// we need to handle the lexing of an identifier here
				// we have to check for an identifier
				stringStart = i;
				if (! ((src[i] >= 'a' && src[i] <= 'z') || (src[i] >= 'A' && src[i] <= 'Z')))
				{
					// identifier must start with a letter
					errors->push_back(LexerErrorInfo(line, col, LEXERR_INVALIDIDENTNAME, "Invalid identifier name. Must begin with a letter.", szOptFile));
					return LEXERR_INVALIDIDENTNAME;
				}

				stringLiteral[i - stringStart] = src[i];

				for (; i < length; i++)
				{
					if (! ((src[i] >= 'a' && src[i] <= 'z') || (src[i] >= 'A' && src[i] <= 'Z') || (src[i] >= '0' && src[i] <= '9')
						|| (src[i] == '_')) )
						break;

					stringLiteral[i - stringStart] = src[i];
				}

				stringLiteral[i - stringStart] = 0;

				if (keys.find(stringLiteral) != keys.end())
				{
					// we have a keyword token
					tok = LexerToken(line, col, keys[stringLiteral], szOptFile);
					tok.str = new char[i - stringStart];
					strcpy(tok.str, stringLiteral);
					tok.str[i - stringStart] = 0;
					tokens->push_back(tok);
				}
				else
				{
					// we have a separate identifier
					tok = LexerToken(line, col, TOK_IDENT, szOptFile);
					tok.str = new char[i - stringStart];
					strcpy(tok.str, stringLiteral);
					tok.str[i - stringStart] = 0;
					tokens->push_back(tok);
				}

				i--; // move back one
				break;
			};

			
		}

		return LEXERR_OK;
	}
}