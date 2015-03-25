#include <iostream>
#include "lexer.h"
int main()
{
	lexer lxr;
	lxr.Tokenize("data.txt");
	return 0;
}