#ifndef _LEXERTOKEN_H
#define _LEXERTOKEN_H
#include <iostream>
#include <string>

namespace Uniscript
{
	// Bitmask for boolean token category.
	#define TOK_CAT_BOOLEAN		0x00000001
	
	// Bitmask for bitwish token category.
	#define TOK_CAT_BITWISE		0x00000010

	// Bitmask for mathematical token category.
	#define TOK_CAT_MATH		0x00000100

	// Bitmask for syntactical token category.
	#define TOK_CAT_SYNTAX		0x00001000

	// Bitmask for reserved words token category.
	#define TOK_CAT_RESERVED	0x00100000

	// Bitmask for identifier token category.
	#define TOK_CAT_IDENT		0x10000000




	// Less than or equal
	#define TOK_LTE			TOK_CAT_BOOLEAN | 0x00

	// Less than
	#define TOK_LT			TOK_CAT_BOOLEAN | 0x01

	// Greater than or equal
	#define TOK_GTE			TOK_CAT_BOOLEAN | 0x02

	// Greater than
	#define TOK_GT			TOK_CAT_BOOLEAN | 0x03

	// Equal
	#define TOK_EQU			TOK_CAT_BOOLEAN | 0x04

	// Not equal
	#define TOK_NE			TOK_CAT_BOOLEAN | 0x05

	// Logical not
	#define TOK_LNOT		TOK_CAT_BOOLEAN | 0x06

	// Logical and
	#define TOK_LAND		TOK_CAT_BOOLEAN | 0x07

	// Logical or
	#define TOK_LOR			TOK_CAT_BOOLEAN | 0x08


	// Bitshift Left
	#define TOK_BSL			TOK_CAT_BITWISE | 0x00

	// Bitshift right
	#define TOK_BSR			TOK_CAT_BITWISE | 0x01

	// Bitshift left and then assign
	#define TOK_BSLEQU		TOK_CAT_BITWISE | 0x02

	// Bitshift right and then assign
	#define TOK_BSREQU		TOK_CAT_BITWISE | 0x03

	// Bitwise and
	#define TOK_BAND		TOK_CAT_BITWISE | 0x04

	// Bitwise or
	#define TOK_BOR			TOK_CAT_BITWISE | 0x05

	// Bitwise or and assign
	#define TOK_BOREQU		TOK_CAT_BITWISE | 0x06

	// Bitwise xor
	#define TOK_BXOR		TOK_CAT_BITWISE | 0x07

	// Bitwise xor and assign
	#define TOK_BXOREQU		TOK_CAT_BITWISE | 0x08

	// Bitwise not
	#define TOK_BNOT		TOK_CAT_BITWISE | 0x09

	// Bitwise not equal
	#define TOK_BNE			TOK_CAT_BITWISE | 0x0A




	// Addition
	#define TOK_ADD			TOK_CAT_MATH | 0x00

	// Increment by 1
	#define TOK_INC			TOK_CAT_MATH | 0x01

	// Subtraction
	#define TOK_SUB			TOK_CAT_MATH | 0x02

	// Decrement by 1
	#define TOK_DEC			TOK_CAT_MATH | 0x03

	// Multiplication
	#define TOK_MUL			TOK_CAT_MATH | 0x04

	// Division
	#define TOK_DIV			TOK_CAT_MATH | 0x05

	// Power
	#define TOK_POW			TOK_CAT_MATH | 0x06

	// Modulo
	#define TOK_MOD			TOK_CAT_MATH | 0x07

	// Modulo and assign
	#define TOK_MODEQU		TOK_CAT_MATH | 0x08

	// Power and assign
	#define TOK_POWEQU		TOK_CAT_MATH | 0x09

	// Addition and assign
	#define TOK_ADDEQU		TOK_CAT_MATH | 0x0A

	// Subtraction and assign
	#define TOK_SUBEQU		TOK_CAT_MATH | 0x0B

	// Multiplication and assign
	#define TOK_MULEQU		TOK_CAT_MATH | 0x0C

	// Division and assign
	#define TOK_DIVEQU		TOK_CAT_MATH | 0x0D




	// Assignment
	#define TOK_ASSIGN		TOK_CAT_SYNTAX | 0x00

	// Left brace
	#define TOK_LBRACE		TOK_CAT_SYNTAX | 0x01

	// Right brace
	#define TOK_RBRACE		TOK_CAT_SYNTAX | 0x02

	// Left bracket
	#define TOK_LBRACK		TOK_CAT_SYNTAX | 0x03

	// Right bracket
	#define TOK_RBRACK		TOK_CAT_SYNTAX | 0x04

	// Left parenthesis
	#define TOK_LPAREN		TOK_CAT_SYNTAX | 0x05

	// Right parenthesis
	#define TOK_RPAREN		TOK_CAT_SYNTAX | 0x06

	// End of statement
	#define TOK_END			TOK_CAT_SYNTAX | 0x07

	// Dot (member accessor)
	#define TOK_DOT			TOK_CAT_SYNTAX | 0x11

	// Comma (separator)
	#define TOK_COMMA		TOK_CAT_SYNTAX | 0x12


	// Character literal
	#define TOK_CHAR		TOK_CAT_SYNTAX | 0x08

	// String literal
	#define TOK_STR			TOK_CAT_SYNTAX | 0x09

	// String literal with no escape
	#define TOK_STRESC		TOK_CAT_SYNTAX | 0x0A

	// Byte literal
	#define TOK_BYTE		TOK_CAT_SYNTAX | 0x0B

	// Short literal
	#define TOK_SHORT		TOK_CAT_SYNTAX | 0x0C

	// Int literal
	#define TOK_INT			TOK_CAT_SYNTAX | 0x0D

	// Long literal
	#define TOK_LONG		TOK_CAT_SYNTAX | 0x0E

	// Float literal
	#define TOK_FLOAT		TOK_CAT_SYNTAX | 0x0F

	// Double literal
	#define TOK_DOUBLE		TOK_CAT_SYNTAX | 0x10




	// 'alias' keyword
	#define TOK_ALIAS		TOK_CAT_RESERVED | 0x00

	// 'break' keyword
	#define TOK_BREAK		TOK_CAT_RESERVED | 0x01

	// 'case' keyword
	#define TOK_CASE		TOK_CAT_RESERVED | 0x02

	// 'class' keyword
	#define TOK_CLASS		TOK_CAT_RESERVED | 0x03

	// 'const' keyword
	#define TOK_CONST		TOK_CAT_RESERVED | 0x04

	// 'continue' keyword
	#define TOK_CONTINUE	TOK_CAT_RESERVED | 0x05

	// 'default' keyword
	#define TOK_DEFAULT		TOK_CAT_RESERVED | 0x06

	// 'delete' keyword
	#define TOK_DELETE		TOK_CAT_RESERVED | 0x07

	// 'do' keyword
	#define TOK_DO			TOK_CAT_RESERVED | 0x08

	// 'else' keyword
	#define TOK_ELSE		TOK_CAT_RESERVED | 0x09

	// 'enum' keyword
	#define TOK_ENUM		TOK_CAT_RESERVED | 0x0A

	// 'false' keyword
	#define TOK_FALSE		TOK_CAT_RESERVED | 0x0B

	// 'finally' keyword
	#define TOK_FINALLY		TOK_CAT_RESERVED | 0x0C

	// 'for' keyword
	#define TOK_FOR			TOK_CAT_RESERVED | 0x0D

	// 'foreach' keyword
	#define TOK_FOREACH		TOK_CAT_RESERVED | 0x0E

	// 'in' keyword
	#define TOK_IN			TOK_CAT_RESERVED | 0x0F

	// 'new' keyword
	#define TOK_NEW			TOK_CAT_RESERVED | 0x10

	// 'null' keyword
	#define TOK_NULL		TOK_CAT_RESERVED | 0x11

	// 'private' keyword
	#define TOK_PRIVATE		TOK_CAT_RESERVED | 0x12

	// 'protected' keyword
	#define TOK_PROTECTED	TOK_CAT_RESERVED | 0x13

	// 'public' keyword
	#define TOK_PUBLIC		TOK_CAT_RESERVED | 0x14

	// 'ref' keyword
	#define TOK_REF			TOK_CAT_RESERVED | 0x15

	// 'return' keyword
	#define TOK_RETURN		TOK_CAT_RESERVED | 0x16

	// 'struct' keyword
	#define TOK_STRUCT		TOK_CAT_RESERVED | 0x17

	// 'switch' keyword
	#define TOK_SWITCH		TOK_CAT_RESERVED | 0x18

	// 'this' keyword
	#define TOK_THIS		TOK_CAT_RESERVED | 0x19

	// 'throw' keyword
	#define TOK_THROW		TOK_CAT_RESERVED | 0x1A

	// 'true' keyword
	#define TOK_TRUE		TOK_CAT_RESERVED | 0x1B

	// 'typeof' keyword
	#define TOK_TYPEOF		TOK_CAT_RESERVED | 0x1B

	// 'while' keyword
	#define TOK_WHILE		TOK_CAT_RESERVED | 0x1C

	// identifier
	#define TOK_IDENT		TOK_CAT_IDENT | 0x00



	// This structure stores information about a Token that was
	// taken from a Uniscript source during lexical analysis.
	struct LexerToken
	{
		LexerToken(unsigned int _line, unsigned int _col, unsigned int _type, std::string _path)
		{
			line = _line;
			col = _col;
			type = _type;
			sourcePath = _path;
			n64 = 0;
		}

		LexerToken()
		{
			line = 0;
			col = 0;
			type = 0;
			sourcePath = "";
			n64 = 0;
		}

		// The line number this token
		// was found on.
		unsigned int line;

		// The column number this token
		// was found in.
		unsigned int col;

		// The type of token this is.
		unsigned int type;

		// The file (full path) this token belongs to.
		std::string sourcePath;


		// This union stores the value
		// for this token. It can be an
		// integral value or a string value.
		// A string value typically stores
		// a string literal or an identifier.
		union
		{
			unsigned char n8;
			unsigned short n16;
			unsigned int n32;
			unsigned long long n64;
			float f32;
			double f64;
			char *str;
		};
	};
}

#endif /* _LEXERTOKEN_H */