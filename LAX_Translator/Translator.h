#pragma once
#include "lexer.h"
#include "LLkTable.h"
#include "LexerStack.h"
#include <stack>
enum NonterminalsStack
{
	 
};

//enum TerminalsStack
//{
//	stCOLON, stID, stENDOFFILE, stSEMICOLON, stDIM, stAS, stTYPE, stEQ, stFOR, stIN, stLEFT, stCMP,
//	stRIGHT, stNEXT, stIF, stTHEN, stELSE, stINPUT, stPRINT, stGOTO, stSWITCH, stCASE, stCONST,
//	stBREAK, stDEFAULT, stEND, stFAIL, stFIRSTPRIORITY, stSECONDPRIORITY
//};
enum TerminalsStack
{
	stDIM, stID, stAS, stTYPE, stSEMICOLON, stCOLON, stENDOFFILE, stEQ, stFOR, stIN, stLEFT, stCMP,
	stRIGHT, stNEXT, stIF, stTHEN, stELSE, stINPUT, stPRINT, stGOTO, stSWITCH, stCASE, stCONST,
	stBREAK, stDEFAULT, stEND, stFAIL, stFIRSTPRIORITY, stSECONDPRIORITY
};

enum ActionsStack
{
	actENDOFFILE, actPRINT, actPUSHID, actPOPOUTOPERATIONS, actSECONDPRIORITY, actPOPID, 
	actLABELKEEP, actJMPKEEP, actJIKEEP, actNEXT, actFORCMP, actFORLABELKEEP, actFORJMPKEEP,
	actCMPINV, actFIRSTPRIORITY, actLEFTPAR, actINPUT, actCMPSWITCH, actPOPDUMP, actFAIL
};

enum MainstackClass
{
	stNonterminal, stTerminal, stAction, stValue, stPointer
};

struct MainstackElement
{
	MainstackClass type;
	int value;
};

struct symbol_token
{
	int priority;
	int token_class;
};

class TokenStack : public std::stack<symbol_token>
{
public:
	int Priority()
	{
		if (empty())
		{
			return -10;
		}
		else
		{
			return top().priority;
		}
	}
};

class Translator
{

	lexr::Lexer stack_lexer;
	lexer lxr;
	LLkTable llk_table;

	std::vector<lexeme_token>& get_lexeme_list() { return lxr.get_lexeme_list(); }

	std::vector<MainstackElement> mainstack;
	TokenStack prioritystack;
	int push_operation(symbol_token token);

	void push(MainstackElement);
	void pop();
	void shift();
	void hold();
	MainstackElement top() const;

	std::unordered_map<int, int> label_keeper;
	std::unordered_map<int, int> jmp_keeper;
	int* new_label() { return new int; }


	int current_lexeme_position;
	int mainstack_top;

	void transliterator(lexeme_token tkn);
	int value_register;
	int class_register;
	Sequence sequence_register;

	int Table();

	void rule1();
	void rule2();
	void rule3();
	void rule4();
	void rule5();
	void rule6();
	void rule7();
	void rule8();
	void rule9();
	void rule10();
	void rule11();
	void rule12();
	void rule13();
	void rule14();
	void rule15();
	void rule16();
	void rule17();
	void rule18();
	void rule19();
	void rule20();
	void rule21();
	void rule22();
	void rule23();
	void rule24();
	void rule25();
	void rule26();
	void rule27();
	void rule28();
	void rule29();
	void rule30();
	void rule31();
	void rule32();
	void rule33();
	void rule34();
	void rule35();
	void rule36();
	void rule37();
	void rule38();
	void rule39();
	void rule40();

	void pop_terminal();
	void pop_id();
	void pop_cmp();

	void action_end();
	void action_print();
	void action_pushid();
	void action_secondPriority();
	void action_firstPriority();
	void action_leftpar();
	void action_popout();
	void action_popid();
	void action_labelkeep();
	void action_jmpkeep();
	void action_jikeep();
	void action_forcmp();
	void action_next();
	void action_forlabelkeep();
	void action_forjmpkeep();
	void action_cmpinv();
	void action_input();
	void action_cmpswitch();
	void action_popdump();
	void action_fail();

	int update_labels();

	int* pointer_one;
	int* pointer_zero;
	int* pointer_fail;
	void set_constant_register(std::string _variable){ stack_lexer.set_constant_register(_variable); }
	void set_variable_register(std::string _variable){ stack_lexer.set_variable_register(_variable); }
	void set_lexeme_class(lexr::LexemeType _class){ stack_lexer.set_lexeme_class(_class); }
	void set_lexeme_value(int _value){ stack_lexer.set_lexeme_value(_value); }
	void AddLexemeToken(){ stack_lexer.AddLexemeToken(); }
	int* get_constant_pointer(std::string constant){ return stack_lexer.get_constant_pointer(constant); }
	void set_pointer_register(int* _pointer){ stack_lexer.set_pointer_register(_pointer); }

	typedef void(Translator::*nonterminal_rule)();
	std::vector<nonterminal_rule> nonterminal_table;

	bool any_errors;

	LongNumber dump;
public:
	void LoadTableFromXML(const std::string& xml_file);
	void BuildTableFromGrammar(const std::string& grammar_file);

	void Translate(const std::string& program);

	void Run();

	Translator();
	~Translator();
};

