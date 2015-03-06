#include <iostream>
#include "lexer.h"
int main()
{
	lexer lxr;
	lxr.Tokenize("prog.txt");
	return 0;
}