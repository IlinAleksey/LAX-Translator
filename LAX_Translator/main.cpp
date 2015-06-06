#include <iostream>
#include "lexer.h"
#include "Translator.h"
int main()
{
	/*lexer lxr;
	lxr.Tokenize("data_lex.txt");*/
	Translator trns;
	trns.BuildTableFromGrammar("");
	trns.Translate("data_lex.txt");
	trns.Run();
	return 0;
	
}