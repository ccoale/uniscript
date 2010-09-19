#ifndef _CODEDOM_H
#define _CODEDOM_H

// The Uniscript CodeDOM organizes pre-lexed tokens into a Document Object Model that provides
// a hierarchial tree of code elements. Below is a list of all elements.
//
// -- Expressions --
// Expression				- a list of tokens that should be evaluated for a single value
//
// -- Code Block --
// CodeBlock				- a series of CodeDOM elements.
//
// -- Declarations --
// VariableDeclaration		- a single variable name, type, and an expression (optional) for its default value
// FunctionDeclaration		- a return type, function name, parameters, then the body as a series of CodeDOM elements.
// ClassDeclaration			- The class name, then a series of method declarations, and member variable declarations.
// StructDeclaration		- The struct name, then a series of member variable declarations.
// MethodDeclaration		- Same as a FunctionDeclaration but with additional attributes for classes.
// MemberVariableDeclaration- Same as VariableDeclaration but with additional attributes
//
// -- Statements --
// WhileStatement			- An expression, followed by a series of CodeDOM elements.
// ForStatement				- A variable initialization, an expression, a variable-updater, followed by a CodeBlock.
// DoWhileStatement			- A CodeBlock followed by an expression.
// AssignStatement			- A variable followed by an expression.
// IfStatement				- An expression and a CodeBlock.
// ElseIfStatement			- An expression and a CodeBlock.
// ElseStatement			- A CodeBlock.
// SwitchStatement			- An expression and a series of CaseStatements.
// CaseStatement			- An expression and a CodeBlock.
// BreakStatement			- Nothing
// ContinueStatement		- Nothing
// ReturnStatement			- An expression.

namespace Uniscript
{
	// CodeDocument is the root container for the CodeDOM of a specific source.
	class CodeDocument
	{
	private:

	};
}

#endif /* _CODEDOM_H */