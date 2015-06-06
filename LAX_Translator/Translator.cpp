#include "Translator.h"
#include "LLkTableBuilder.h"

Translator::Translator():
nonterminal_table({ &Translator::rule1, &Translator::rule2, &Translator::rule3,
&Translator::rule4, &Translator::rule5, &Translator::rule6, &Translator::rule7,
&Translator::rule8, &Translator::rule9, &Translator::rule10, &Translator::rule11,
&Translator::rule12, &Translator::rule13, &Translator::rule14, &Translator::rule15,
&Translator::rule16, &Translator::rule17, &Translator::rule18, &Translator::rule19,
&Translator::rule20, &Translator::rule21, &Translator::rule22, &Translator::rule23,
&Translator::rule24, &Translator::rule25, &Translator::rule26, &Translator::rule27,
&Translator::rule28, &Translator::rule29, &Translator::rule30,
&Translator::rule31, &Translator::rule32, &Translator::rule33,
&Translator::rule34, &Translator::rule35, &Translator::rule36,
&Translator::rule37, &Translator::rule38, &Translator::rule39, &Translator::rule40 })
{
	current_lexeme_position = 0;
	mainstack_top = -1;

	//add one to constants
	pointer_one = get_constant_pointer("1");
	pointer_zero = get_constant_pointer("0");
	pointer_fail = get_constant_pointer("9876543210");
	any_errors = false;
}


Translator::~Translator()
{
}

void Translator::push(MainstackElement element)
{
	if (mainstack_top + 1 >= mainstack.size())
	{
		mainstack.push_back(element);
	}
	else
	{
		mainstack[mainstack_top + 1] = element;
	}
	
	mainstack_top++;
}
void Translator::pop()
{
	mainstack_top--;
}
void Translator::shift()
{
	current_lexeme_position++;
}
void Translator::hold()
{

}
MainstackElement Translator::top() const
{
	return mainstack[mainstack_top];
}

void Translator::rule1()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[1].get_value() });
	push({ MainstackClass::stNonterminal, sequence_register[0].get_value() });

}

void Translator::rule2()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[0].get_value() });
}

void Translator::rule3()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[4].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[3].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[2].get_value() });
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actPOPID });
	push({ MainstackClass::stValue, (int) pointer_zero });
	push({ MainstackClass::stAction, actPUSHID });
	push({ MainstackClass::stPointer, 4 });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}

void Translator::rule4()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[5].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[4].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[3].get_value() });
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actPOPID });
	push({ MainstackClass::stValue, (int) pointer_zero });
	push({ MainstackClass::stAction, actPUSHID });
	push({ MainstackClass::stPointer, 4 });
	push({ MainstackClass::stTerminal, sequence_register[2].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}

void Translator::rule5()
{
	pop();
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}

void Translator::rule6()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[3].get_value() });

	push({ MainstackClass::stNonterminal, sequence_register[2].get_value() });

	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actLABELKEEP });

	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });

	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule7()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[1].get_value() });
	push({ MainstackClass::stNonterminal, sequence_register[0].get_value() });
}
void Translator::rule8()
{
	pop();
	push({ MainstackClass::stAction, ActionsStack::actENDOFFILE });
	push({ MainstackClass::stTerminal, TerminalsStack::stENDOFFILE });
	
}
void Translator::rule9()
{
	pop();
	push({ MainstackClass::stTerminal, TerminalsStack::stSEMICOLON });
}
void Translator::rule10()
{
	pop();
	push({ MainstackClass::stTerminal, sequence_register[3].get_value() });
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actPOPID });
	push({ MainstackClass::stNonterminal, sequence_register[2].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stPointer, 4 });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule11()
{
	int label1 = (int) new_label();
	int label2 = (int) new_label();
	pop();
	push({ MainstackClass::stValue, label1 });									//{labelkeep}.value
	push({ MainstackClass::stAction, actLABELKEEP });							//{labelkeep}
	push({ MainstackClass::stTerminal, sequence_register[11].get_value() });	//;
	push({ MainstackClass::stValue, 0 });										//{labelkeep}.other
	push({ MainstackClass::stValue, 0 });										//{labelkeep}.to
	push({ MainstackClass::stValue, 0 });										//{labelkeep}.value
	push({ MainstackClass::stAction, actFORJMPKEEP });							//{labelkeep}
	push({ MainstackClass::stPointer, 2 });										//id.pointer
	push({ MainstackClass::stTerminal, sequence_register[10].get_value() });	//id
	push({ MainstackClass::stValue, 0 });										//{next}.value
	push({ MainstackClass::stAction, actNEXT });								//{next}
	push({ MainstackClass::stNonterminal, sequence_register[9].get_value() });	//<programnext>
	push({ MainstackClass::stValue, label1 });									//{JIKEEP}.value
	push({ MainstackClass::stAction, actJIKEEP });								//{JIKEEP}
	push({ MainstackClass::stValue, 0 });										//{FORCMP}.value
	push({ MainstackClass::stAction, actFORCMP });								//{FORCMP}
	push({ MainstackClass::stTerminal, sequence_register[8].get_value() });		//)
	push({ MainstackClass::stNonterminal, sequence_register[7].get_value() });	//<expression>
	push({ MainstackClass::stPointer, 4 });										//cmp.pointer
	push({ MainstackClass::stTerminal, sequence_register[6].get_value() });		//cmp
	push({ MainstackClass::stNonterminal, sequence_register[5].get_value() });	//<expression>
	push({ MainstackClass::stTerminal, sequence_register[4].get_value() });		//(
	push({ MainstackClass::stTerminal, sequence_register[3].get_value() });		//in
	push({ MainstackClass::stPointer, 14 });									//id.pointer
	push({ MainstackClass::stTerminal, sequence_register[2].get_value() });		//id
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });		//for
	push({ MainstackClass::stValue, 0 });										//{labelkeep}.value
	push({ MainstackClass::stAction, actFORLABELKEEP });						//{labelkeep}
	push({ MainstackClass::stPointer,  2});										//id.pointer
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });		//id
}
void Translator::rule12()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[3].get_value() });

	push({ MainstackClass::stNonterminal, sequence_register[2].get_value() });

	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actLABELKEEP });

	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });

	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule13()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[1].get_value() });
	push({ MainstackClass::stNonterminal, sequence_register[0].get_value() });

}
void Translator::rule14()
{
	pop();
	push({ MainstackClass::stTerminal, TerminalsStack::stNEXT });
}

void Translator::rule15()
{
	int label1 = (int) new_label();
	pop();
	push({ MainstackClass::stTerminal, sequence_register[6].get_value() });			//;
	push({ MainstackClass::stNonterminal, sequence_register[5].get_value() });		//<else>
	push({ MainstackClass::stTerminal, sequence_register[4].get_value() });			//then
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actCMPINV });
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actPUSHID });
	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stNonterminal, sequence_register[3].get_value() });			//id
	push({ MainstackClass::stPointer, 6 });
	push({ MainstackClass::stTerminal, sequence_register[2].get_value() });			//cmp
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actPUSHID });
	push({ MainstackClass::stPointer, 2 });											//id.value
	push({ MainstackClass::stNonterminal, sequence_register[1].get_value() });			//id
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });			//if
}
void Translator::rule16()
{
	pop();
	
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actJMPKEEP });
	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stTerminal, sequence_register[2].get_value() });			//id
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });			//else
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actJIKEEP });
	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });			//id
}
void Translator::rule17()
{
	pop();
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actJIKEEP });
	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });			//id
}
void Translator::rule18()
{
	pop();
	push({ MainstackClass::stTerminal, sequence_register[2].get_value() });
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actINPUT });
	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule19()
{
	pop();
	push({ MainstackClass::stTerminal, sequence_register[2].get_value() });
	push({ MainstackClass::stAction, ActionsStack::actPRINT });
	push({ MainstackClass::stNonterminal, sequence_register[1].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule20()
{
	pop();
	push({ MainstackClass::stTerminal, sequence_register[2].get_value() });
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actJMPKEEP });
	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule21()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[4].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[3].get_value() });
	push({ MainstackClass::stNonterminal, sequence_register[2].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });

}
void Translator::rule22()
{
	int label1 = (int)new_label();
	int label2 = (int) new_label();
	pop();
	push({ MainstackClass::stValue, label2 });
	push({ MainstackClass::stAction, actLABELKEEP });
	push({ MainstackClass::stNonterminal, sequence_register[4].get_value() });
	push({ MainstackClass::stValue, label1 });
	push({ MainstackClass::stAction, actLABELKEEP });
	push({ MainstackClass::stValue, label2 });
	push({ MainstackClass::stAction, actJMPKEEP });
	push({ MainstackClass::stNonterminal, sequence_register[3].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[2].get_value() });
	push({ MainstackClass::stValue, label1 });
	push({ MainstackClass::stAction, actJIKEEP });
	push({ MainstackClass::stAction, actCMPSWITCH });
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actPUSHID });
	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule23()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[3].get_value() });

	push({ MainstackClass::stNonterminal, sequence_register[2].get_value() });

	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actLABELKEEP });

	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });

	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule24()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[1].get_value() });
	push({ MainstackClass::stNonterminal, sequence_register[0].get_value() });
}
void Translator::rule25()
{
	pop();
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule26()
{
	pop();
	push({ MainstackClass::stTerminal, sequence_register[6].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[5].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[4].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[3].get_value() });
	push({ MainstackClass::stNonterminal, sequence_register[2].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
	push({ MainstackClass::stAction, actPOPDUMP });
}
void Translator::rule27()
{
	pop();
	push({ MainstackClass::stTerminal, sequence_register[3].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[2].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
	push({ MainstackClass::stAction, actPOPDUMP });
}
void Translator::rule28()
{
	int label1 = (int) new_label();
	int label2 = (int) new_label();
	pop();
	push({ MainstackClass::stValue, label2 });
	push({ MainstackClass::stAction, actLABELKEEP });
	push({ MainstackClass::stNonterminal, sequence_register[5].get_value() });
	push({ MainstackClass::stValue, label1 });
	push({ MainstackClass::stAction, actLABELKEEP });
	push({ MainstackClass::stValue, label2 });
	push({ MainstackClass::stAction, actJMPKEEP });
	push({ MainstackClass::stNonterminal, sequence_register[4].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[3].get_value() });
	push({ MainstackClass::stValue, label1 });
	push({ MainstackClass::stAction, actJIKEEP });
	push({ MainstackClass::stAction, actCMPSWITCH });
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actPUSHID });
	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stTerminal, sequence_register[2].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule29()
{
	pop();
	push({ MainstackClass::stTerminal, sequence_register[7].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[6].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[5].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[4].get_value() });
	push({ MainstackClass::stNonterminal, sequence_register[3].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[2].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stAction, actPOPDUMP });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule30()
{
	pop();
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stAction, actFAIL });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule31()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[0].get_value() });
}
void Translator::rule32()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[2].get_value() });
	push({ MainstackClass::stNonterminal, sequence_register[1].get_value() });
	push({ MainstackClass::stAction, actLEFTPAR });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });

}
void Translator::rule33()
{
	pop();
	push({ MainstackClass::stAction, actPOPOUTOPERATIONS });
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actPUSHID });
	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stNonterminal, sequence_register[0].get_value() });
}
void Translator::rule34()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[2].get_value() });
	push({ MainstackClass::stAction, actFIRSTPRIORITY });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actPUSHID });
	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stNonterminal, sequence_register[0].get_value() });
}
void Translator::rule35()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[2].get_value() });
	push({ MainstackClass::stAction, actSECONDPRIORITY });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stValue, 0 });
	push({ MainstackClass::stAction, actPUSHID });
	push({ MainstackClass::stPointer, 2 });
	push({ MainstackClass::stNonterminal, sequence_register[0].get_value() });
}
void Translator::rule36()
{
	pop();
	push({ MainstackClass::stAction, actPOPOUTOPERATIONS });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule37()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[2].get_value() });
	push({ MainstackClass::stAction, actFIRSTPRIORITY });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule38()
{
	pop();
	push({ MainstackClass::stNonterminal, sequence_register[2].get_value() });
	push({ MainstackClass::stAction, actSECONDPRIORITY });
	push({ MainstackClass::stTerminal, sequence_register[1].get_value() });
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule39()
{
	pop();
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}
void Translator::rule40()
{
	pop();
	push({ MainstackClass::stTerminal, sequence_register[0].get_value() });
}

void Translator::pop_terminal()
{
	pop();
	shift();
}
void Translator::pop_id()
{
	int pointer = mainstack[mainstack_top - 1].value;
	mainstack[mainstack_top - 1 - pointer].value = value_register;
	pop();
	pop();
	shift();
}

void Translator::pop_cmp()
{
	int pointer = mainstack[mainstack_top - 1].value;
	mainstack[mainstack_top - 1 - pointer].value = value_register;
	pop();
	pop();
	shift();
}

void Translator::action_end()
{
	set_lexeme_class(lexr::END_LEX);
	set_lexeme_value(0);
	AddLexemeToken();
	pop();
}

void Translator::action_print()
{
	set_lexeme_class(lexr::WRITE);
	set_lexeme_value(0);
	AddLexemeToken();
	set_lexeme_class(lexr::LexemeType::POP);
	set_pointer_register((int*) &dump);
	AddLexemeToken();
	pop();
}

void Translator::action_pushid()
{
	set_lexeme_class(lexr::PUSH);
	set_pointer_register((int*) mainstack[mainstack_top - 1].value);
	AddLexemeToken();
	pop();
	pop();
}

void Translator::action_secondPriority()
{
	symbol_token operation_token = { 2, value_register };
	push_operation(operation_token);
	pop();
}

void Translator::action_firstPriority()
{
	symbol_token operation_token = { 3, value_register };
	push_operation(operation_token);
	pop();
}

void Translator::action_leftpar()
{
	symbol_token operation_token = { 0, value_register };
	push_operation(operation_token);
	pop();
}

void Translator::action_popout()
{
	while (1 <= prioritystack.Priority())
	{
		if (prioritystack.top().token_class == MINUS ||
			prioritystack.top().token_class == DIVISION ||
			prioritystack.top().token_class == MOD)
		{
			LongNumber* first = new LongNumber;
			LongNumber* second = new LongNumber;
			set_lexeme_class(lexr::LexemeType::POP);
			stack_lexer.set_pointer_register((int*) first);
			AddLexemeToken();
			set_lexeme_class(lexr::LexemeType::POP);
			stack_lexer.set_pointer_register((int*) second);
			AddLexemeToken();
			set_lexeme_class(lexr::LexemeType::PUSH);
			stack_lexer.set_pointer_register((int*) first);
			AddLexemeToken();
			set_lexeme_class(lexr::LexemeType::PUSH);
			stack_lexer.set_pointer_register((int*) second);
			AddLexemeToken();

			delete first;
			delete second;
		}
		set_lexeme_class(lexr::OPERATION);
		set_lexeme_value(prioritystack.top().token_class);
		AddLexemeToken();
		prioritystack.pop();
	}
	if (prioritystack.Priority() == 0)
	{
		prioritystack.pop();
	}
	pop();
}

void Translator::action_popid()
{
	set_lexeme_class(lexr::POP);
	set_pointer_register((int*) mainstack[mainstack_top - 1].value);
	AddLexemeToken();
	pop();
	pop();
}

void Translator::action_labelkeep()
{
	int current_line = stack_lexer.GetLexemeList().size();
		
		
	//label_keeper[current_line] = mainstack[mainstack_top - 1].value;
	label_keeper[mainstack[mainstack_top - 1].value] = current_line;
	pop();
	pop();
}

void Translator::action_jmpkeep()
{
	int current_line = stack_lexer.GetLexemeList().size();
	//label_keeper[current_line] = mainstack[mainstack_top - 1].value;
	jmp_keeper[mainstack[mainstack_top - 1].value] = current_line;
	set_lexeme_class(lexr::JUMP);
	set_pointer_register(pointer_zero);
	AddLexemeToken();
	pop();
	pop();
}

void Translator::action_jikeep()
{
	int current_line = stack_lexer.GetLexemeList().size();
	//label_keeper[current_line] = mainstack[mainstack_top - 1].value;
	jmp_keeper[mainstack[mainstack_top - 1].value] = current_line;
	set_lexeme_class(lexr::JUMP_IF);
	set_pointer_register(pointer_zero);
	AddLexemeToken();
	pop();
	pop();
}

void Translator::action_forcmp()
{
	int cmp = mainstack[mainstack_top - 1].value;
	if (cmp != relationship_type::LESS)
	{
		any_errors = true;
	}
	else
	{
		set_lexeme_class(lexr::LexemeType::RELATION);
		stack_lexer.set_relation_register(lexr::RelationType::LESSEQUAL);
		AddLexemeToken();
		pop();
		pop();
	}
}
void Translator::action_next()
{
	int* var_pointer = (int*) mainstack[mainstack_top - 1].value;
	set_lexeme_class(lexr::PUSH);
	set_pointer_register(var_pointer);
	AddLexemeToken();
	set_lexeme_class(lexr::LexemeType::PUSH);
	set_pointer_register(pointer_one);
	AddLexemeToken();
	set_lexeme_class(lexr::OPERATION);
	set_lexeme_value(lexr::OperationType::PLUS);
	AddLexemeToken();
	set_lexeme_class(lexr::POP);
	set_pointer_register(var_pointer);
	AddLexemeToken();
	pop();
	pop();
}

void Translator::action_forlabelkeep()
{
	mainstack[mainstack_top - 24].value = mainstack[mainstack_top - 1].value;
	mainstack[mainstack_top - 23].value = stack_lexer.GetLexemeList().size();
	pop();
	pop();

}
void Translator::action_forjmpkeep()
{
	if (mainstack[mainstack_top - 3].value != mainstack[mainstack_top - 1].value)
	{
		any_errors = true;
	}
	else
	{
		int line_to = mainstack[mainstack_top - 2].value + 1;
		int* line_to_pointer = get_constant_pointer(std::to_string(line_to));

		set_lexeme_class(lexr::JUMP);
		set_pointer_register(line_to_pointer);
		AddLexemeToken();
		pop();
		pop();
		pop();
		pop();

	}
	
}

void Translator::action_cmpinv()
{
	int relation = mainstack[mainstack_top - 1].value;
	/*switch (relation)
	{
	case lexr::MORE:
		relation = lexr::LESSEQUAL;
		break;
	case lexr::LESS:
		relation = lexr::MOREEQUAL;
		break;
	case lexr::EQUAL:
		relation = lexr::NOTEQUAL;
		break;
	case lexr::MOREEQUAL:
		relation = lexr::LESS;
		break;
	case lexr::LESSEQUAL:
		relation = lexr::MORE;
		break;
	case lexr::NOTEQUAL:
		relation = lexr::EQUAL;
		break;
	default:
		break;
	}*/
	switch (relation)
	{
	case MORE:
		relation = lexr::LESSEQUAL;
		break;
	case LESS:
		relation = lexr::MOREEQUAL;
		break;
	case GREATER_OR_EQUAL:
		relation = lexr::LESS;
		break;
	case LESS_OR_EQUAL:
		relation = lexr::MORE;
		break;
	case NOT_EQUAL:
		relation = lexr::NOTEQUAL;
		break;
	case EQUAL_EQUAL:
		relation = lexr::EQUAL;
		break;
	case LAST_RELATIONSHIP_TYPE:
		break;
	default:
		break;
	}
	set_lexeme_class(lexr::LexemeType::RELATION);
	stack_lexer.set_relation_register((lexr::RelationType)relation);
	AddLexemeToken();
	pop();
	pop();
}

void Translator::action_input()
{
	set_lexeme_class(lexr::READ);
	set_lexeme_value(0);
	AddLexemeToken();
	set_lexeme_class(lexr::POP);
	set_pointer_register((int*) mainstack[mainstack_top - 1].value);
	AddLexemeToken();
	pop();
	pop();
}

void Translator::action_fail()
{
	set_lexeme_class(lexr::LexemeType::PUSH);
	set_pointer_register(pointer_fail);
	AddLexemeToken();
	set_lexeme_class(lexr::WRITE);
	set_lexeme_value(0);
	AddLexemeToken();
	set_lexeme_class(lexr::LexemeType::END_LEX);
	set_lexeme_value(0);
	AddLexemeToken();
	pop();
}

void Translator::action_cmpswitch()
{
	LongNumber* valuekeep = new LongNumber;
	LongNumber* valuecmpkeep = new LongNumber;
	set_lexeme_class(lexr::LexemeType::POP);
	stack_lexer.set_pointer_register((int*) valuecmpkeep);
	AddLexemeToken();
	set_lexeme_class(lexr::LexemeType::POP);
	stack_lexer.set_pointer_register((int*) valuekeep);
	AddLexemeToken();
	set_lexeme_class(lexr::LexemeType::PUSH);
	stack_lexer.set_pointer_register((int*) valuekeep);
	AddLexemeToken();
	set_lexeme_class(lexr::LexemeType::PUSH);
	stack_lexer.set_pointer_register((int*) valuecmpkeep);
	AddLexemeToken();

	set_lexeme_class(lexr::LexemeType::RELATION);
	stack_lexer.set_relation_register(lexr::RelationType::NOTEQUAL);
	AddLexemeToken();

	set_lexeme_class(lexr::LexemeType::POP);
	stack_lexer.set_pointer_register((int*) valuecmpkeep);
	AddLexemeToken();
	set_lexeme_class(lexr::LexemeType::PUSH);
	stack_lexer.set_pointer_register((int*) valuekeep);
	AddLexemeToken();
	set_lexeme_class(lexr::LexemeType::PUSH);
	stack_lexer.set_pointer_register((int*) valuecmpkeep);
	AddLexemeToken();

	/*delete valuekeep;
	delete valuecmpkeep;*/

	pop();
}
void Translator::action_popdump()
{
	set_lexeme_class(lexr::LexemeType::POP);
	set_pointer_register((int*) &dump);
	AddLexemeToken();
	pop();
}

int  Translator::push_operation(symbol_token token)
{
	if (token.priority == 0)
	{
		prioritystack.push(token);
	}
	else if (token.priority>prioritystack.Priority())
	{
		prioritystack.push(token);
	}
	else
	{
		while (token.priority <= prioritystack.Priority())
		{
			if (prioritystack.top().token_class == MINUS ||
				prioritystack.top().token_class == DIVISION || 
				prioritystack.top().token_class == MOD)
			{
				LongNumber* first = new LongNumber;
				LongNumber* second = new LongNumber;
				set_lexeme_class(lexr::LexemeType::POP);
				stack_lexer.set_pointer_register((int*) first);
				AddLexemeToken();
				set_lexeme_class(lexr::LexemeType::POP);
				stack_lexer.set_pointer_register((int*) second);
				AddLexemeToken();
				set_lexeme_class(lexr::LexemeType::PUSH);
				stack_lexer.set_pointer_register((int*) first);
				AddLexemeToken();
				set_lexeme_class(lexr::LexemeType::PUSH);
				stack_lexer.set_pointer_register((int*) second);
				AddLexemeToken();

				delete first;
				delete second;
			}
			set_lexeme_class(lexr::OPERATION);
			set_lexeme_value(prioritystack.top().token_class);
			AddLexemeToken();
			prioritystack.pop();
		}
		if (token.priority != 1)
		{
			prioritystack.push(token);
		}
		else
		{
			prioritystack.pop();
		}
	}
	return 0;
}

void Translator::transliterator(lexeme_token tkn)
{
	switch (tkn.type)
	{
	case ID:
		class_register = TerminalsStack::stID;
		value_register = tkn.value;
		break;
	case CONSTANT:
		class_register = TerminalsStack::stCONST;
		value_register = tkn.value;
		break;
	case PUNCTUATOR_LEXEME:
		switch (tkn.value)
		{
		case SEMICOLON:
			class_register = TerminalsStack::stSEMICOLON;
			value_register = tkn.value;
			break;
		case LEFT_BRACKET:
			class_register = TerminalsStack::stLEFT;
			value_register = tkn.value;
			break;
		case RIGHT_BRACKET:
			class_register = TerminalsStack::stRIGHT;
			value_register = tkn.value;
			break;
		default:
			break;
		}
		break;
	case ASSIGNMENT:
		class_register = TerminalsStack::stEQ;
		value_register = tkn.value;
		break;
	case OPERATION_LEXEME:
		switch (tkn.value)
		{
		case PLUS:
			class_register = TerminalsStack::stSECONDPRIORITY;
			value_register = tkn.value;
			break;
		case MINUS:
			class_register = TerminalsStack::stSECONDPRIORITY;
			value_register = tkn.value;
			break;
		case MULTIPLICATION:
			class_register = TerminalsStack::stFIRSTPRIORITY;
			value_register = tkn.value;
			break;
		case DIVISION:
			class_register = TerminalsStack::stFIRSTPRIORITY;
			value_register = tkn.value;
			break;
		case MOD:
			class_register = TerminalsStack::stFIRSTPRIORITY;
			value_register = tkn.value;
			break;
		case LAST_OPERATION_TYPE:
			break;
		default:
			break;
		}
		break;
	case TYPE:
		class_register = TerminalsStack::stTYPE;
		value_register = tkn.value;
		break;
	case COLON_LEXEME:
		class_register = TerminalsStack::stCOLON;
		value_register = tkn.value;
		break;
	case LABEL:
		break;
	case RELATIONSHIP_LEXEME:
		switch (tkn.value)
		{
		case MORE:
			class_register = TerminalsStack::stCMP;
			value_register = tkn.value;
			break;
		case LESS:
			class_register = TerminalsStack::stCMP;
			value_register = tkn.value;
			break;
		case EQUAL:
			break;
		case NOT:
			break;
		case GREATER_OR_EQUAL:
			class_register = TerminalsStack::stCMP;
			value_register = tkn.value;
			break;
		case LESS_OR_EQUAL:
			class_register = TerminalsStack::stCMP;
			value_register = tkn.value;
			break;
		case NOT_EQUAL:
			class_register = TerminalsStack::stCMP;
			value_register = tkn.value;
			break;
		case EQUAL_EQUAL:
			class_register = TerminalsStack::stCMP;
			value_register = tkn.value;
			break;
		case LAST_RELATIONSHIP_TYPE:
			break;
		default:
			break;
		}
		break;
	case EMPTY:
		break;
	case DIM:
		class_register = TerminalsStack::stDIM;
		value_register = tkn.value;
		break;
	case AS:
		class_register = TerminalsStack::stAS;
		value_register = tkn.value;
		break;
	case FOR:
		class_register = TerminalsStack::stFOR;
		value_register = tkn.value;
		break;
	case IN:
		class_register = TerminalsStack::stIN;
		value_register = tkn.value;
		break;
	case NEXT:
		class_register = TerminalsStack::stNEXT;
		value_register = tkn.value;
		break;
	case IF:
		class_register = TerminalsStack::stIF;
		value_register = tkn.value;
		break;
	case THEN:
		class_register = TerminalsStack::stTHEN;
		value_register = tkn.value;
		break;
	case ELSE:
		class_register = TerminalsStack::stELSE;
		value_register = tkn.value;
		break;
	case INPUT:
		class_register = TerminalsStack::stINPUT;
		break;
	case PRINT:
		class_register = TerminalsStack::stPRINT;
		break;
	case GOTO:
		class_register = TerminalsStack::stGOTO;
		break;
	case SWITCH:
		class_register = TerminalsStack::stSWITCH;
		break;
	case CASE:
		class_register = TerminalsStack::stCASE;
		break;
	case BREAK:
		class_register = TerminalsStack::stBREAK;
		break;
	case DEFAULT:
		class_register = TerminalsStack::stDEFAULT;
		break;
	case END:
		class_register = TerminalsStack::stEND;
		break;
	case FAIL:
		class_register = TerminalsStack::stFAIL;
		break;
	case ERROR_LEXEME:
		break;
	case NONE:
		break;
	case EXIT_LEXEME:
		class_register = TerminalsStack::stENDOFFILE;
		break;
	case LAST_LEXEME_TYPE:
		break;
	default:
		break;
	}
}

int Translator::Table()
{
	switch (top().type)
	{
	case stNonterminal:
		int _value_register;
		int _class_register;
		if (current_lexeme_position < get_lexeme_list().size() - 1)
		{
			transliterator(get_lexeme_list()[current_lexeme_position]);
			_value_register = value_register;
			_class_register = class_register;
			transliterator(get_lexeme_list()[current_lexeme_position+1]);
			Sequence current_sequence;
			current_sequence.push_back(Symbol(true, _class_register));
			current_sequence.push_back(Symbol(true, class_register));
			class_register = _class_register;
			value_register = _value_register;
			LLkTableAction llkAction = llk_table.get_action(top().value, current_sequence);
			
			if (llkAction.type != LLkTableActionClass::Replace)
			{
				any_errors = true;
				return 1;
			}

			int rule_index = llkAction.value;
			sequence_register = llkAction.sequence;

			(this->*nonterminal_table[rule_index])();
		}
		else
		{
			transliterator(get_lexeme_list()[current_lexeme_position]);
			Sequence current_sequence(Symbol(true, class_register));
			LLkTableAction llkAction = llk_table.get_action(top().value, current_sequence);

			int rule_index = llkAction.value;
			sequence_register = llkAction.sequence;

			(this->*nonterminal_table[rule_index])();
		}
		
		break;
	case stTerminal:
		transliterator(get_lexeme_list()[current_lexeme_position]);
		if (class_register != top().value)
		{
			any_errors = true;
			return 1;
		}
		switch (top().value)
		{
		case stID:
			pop_id();
			break;
		case stCONST:
			pop_id();
			break;
		case stCMP:
			pop_cmp();
			break;
		default:
			pop_terminal();
			break;
		}
		break;
	case stAction:
		switch (top().value)
		{

		case actENDOFFILE:
			action_end();
			break;
		case actPRINT:
			action_print();
			break;
		case actPUSHID:
			action_pushid();
			break;
		case actSECONDPRIORITY:
			action_secondPriority();
			break;
		case actFIRSTPRIORITY:
			action_firstPriority();
			break;
		case actLEFTPAR:
			action_leftpar();
			break;
		case actPOPOUTOPERATIONS:
			action_popout();
			break;
		case actPOPID:
			action_popid();
			break;
		case actLABELKEEP:
			action_labelkeep();
			break;
		case actJMPKEEP:
			action_jmpkeep();
			break;
		case actJIKEEP:
			action_jikeep();
			break;
		case actFORCMP:
			action_forcmp();
			break;
		case actNEXT:
			action_next();
			break;
		case actFORLABELKEEP:
			action_forlabelkeep();
			break;
		case actFORJMPKEEP:
			action_forjmpkeep();
			break;
		case actCMPINV:
			action_cmpinv();
			break;
		case actINPUT:
			action_input();
			break;
		case actCMPSWITCH:
			action_cmpswitch();
			break;
		case actPOPDUMP:
			action_popdump();
			break;
		case actFAIL:
			action_fail();
			break;
		default:
			break;
		}
		break;
	case stValue:
		break;
	case stPointer:
		break;
	default:
		break;
	}
	return 0;
}

int Translator::update_labels()
{
	for each (auto pair in jmp_keeper)
	{
		int pointer = pair.first;
		int line_from = pair.second;
		std::unordered_map<int, int>::iterator position = label_keeper.find(pointer);
		if (position == label_keeper.end())
		{
			any_errors = true;
			return 1;
		}
		else
		{
			int line_to = (*position).second + 1;
			int line_to_pointer = (int) get_constant_pointer(std::to_string(line_to));
			stack_lexer.update_value(line_from, line_to_pointer);

		}
	}
	return 0;
}

void Translator::LoadTableFromXML(const std::string& xml_file)
{

}
void Translator::BuildTableFromGrammar(const std::string& grammar_file)
{
	LLkTableBuilder builder(2);
	bool pass = builder.build_oracle();
	if (pass)
	{
		std::cout << "llk" << std::endl;
	}
	else
	{
		std::cout << "not" << std::endl;
	}
	llk_table = builder.llk_table;
}

void Translator::Translate(const std::string& program)
{
	lxr.Tokenize(program);
	push({ MainstackClass::stNonterminal, 0 });
	while (mainstack_top >= 0 || current_lexeme_position < get_lexeme_list().size())
	{
		
		Table();
		if (any_errors)
		{
			break;
		}
	}
	update_labels();
	if (any_errors)
	{
		std::cout << "Syntax error" << std::endl;
	}
}

void Translator::Run()
{
	std::string binary_file =  stack_lexer.toByteCode();
	stack_lexer.Execute(binary_file);
}

