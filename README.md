# Uniscript
Uniscript is similar to C++ and JavaScript. Below is a sample source. It is _very much_ a work-in-progress still and in its very early stages.
It is not stable and currently going under reconstruction.


------------------------------------------------------
Basic hello world example.
------------------------------------------------------

import iostream;

int main(string[] args)
{
	print("Hello, World!");
	
	return 0;
}

------------------------------------------------------
Creating a class.
------------------------------------------------------

import iostream;

class Display
{
	public string Text;
	
	public void ShowText()
	{
		print(Text);
	}
}

int main(string[] args)
{
	Display disp = new Display;
	
	foreach (string arg in args)
	{
		disp.Text = arg;
		disp.ShowText();
	}
	
	return 0;
}

------------------------------------------------------------------------
BUILT-IN DATA TYPES
------------------------------------------------------------------------
NAME		| DESCRIPTION						| EXAMPLE
------------------------------------------------------------------------
string		| collection of unic. characters	| string x = "Hello World";
char		| single unic. character			| char x = 'A';
byte		| single byte						| byte x = 250;
ushort		| unsigned short					| ushort x = 55000;
short		| signed short						| short x = -32000;
uint		| unsigned int						| uint x = 4563320;
int			| signed int						| int x = -3542769;
ulong		| unsigned long						| ulong x = 1567678997;
long		| signed long						| long x = -37655029159;
object		| base object class for all classes	| object x = new AnyClass;
type		| information about a type			| type x = typeof(int);



Arrays of any type can be created using the following code:
type[] name = new type[number_of_elements] { default value list };
type[] name = new type[number_of_elements];
type[] name = {default value list};
char[] text = "Hello World";
