#include "ProductionLexer.h"
#include <fstream>

ProductionLexer::ProductionLexer():
fsm_table(pLAST_STATE, std::vector<production_lexer_method>(LAST_TRANSLITERATOR_CLASS, &ProductionLexer::error_method)),
current_row(0),
current_column(0),
terminal_symbols_size(0),
nonterminal_symbols_size(0),
current_state(State::pA1)
{
	fsm_table[State::pA1][TransliteratorClass::less] = &ProductionLexer::B1a;
	fsm_table[State::pA1][TransliteratorClass::whitespace] = &ProductionLexer::stay;
	fsm_table[State::pA1][TransliteratorClass::newline] = &ProductionLexer::stay;
	fsm_table[State::pA1][TransliteratorClass::end] = &ProductionLexer::exit_bad;

	fsm_table[State::pB1][TransliteratorClass::symbol] = &ProductionLexer::B2a;
	fsm_table[State::pB1][TransliteratorClass::whitespace] = &ProductionLexer::stay;
	fsm_table[State::pB1][TransliteratorClass::end] = &ProductionLexer::exit_bad;

	fsm_table[State::pB2][TransliteratorClass::symbol] = &ProductionLexer::B2b;
	fsm_table[State::pB2][TransliteratorClass::more] = &ProductionLexer::C1a;
	fsm_table[State::pB2][TransliteratorClass::whitespace] = &ProductionLexer::stay;
	fsm_table[State::pB2][TransliteratorClass::end] = &ProductionLexer::exit_bad;

	
	fsm_table[State::pC1][TransliteratorClass::colon] = &ProductionLexer::C2a;
	fsm_table[State::pC1][TransliteratorClass::end] = &ProductionLexer::exit_bad;
	
	fsm_table[State::pC2][TransliteratorClass::colon] = &ProductionLexer::C3a;
	fsm_table[State::pC2][TransliteratorClass::end] = &ProductionLexer::exit_bad;

	fsm_table[State::pC3][TransliteratorClass::equals] = &ProductionLexer::D1a;
	fsm_table[State::pC3][TransliteratorClass::end] = &ProductionLexer::exit_bad;


	
	fsm_table[State::pD1][TransliteratorClass::quote] = &ProductionLexer::E1a;
	fsm_table[State::pD1][TransliteratorClass::less] = &ProductionLexer::F1a;
	fsm_table[State::pD1][TransliteratorClass::whitespace] = &ProductionLexer::stay;
	fsm_table[State::pD1][TransliteratorClass::end] = &ProductionLexer::exit_bad;



	fsm_table[State::pE1][TransliteratorClass::symbol] = &ProductionLexer::E2a;
	fsm_table[State::pE1][TransliteratorClass::whitespace] = &ProductionLexer::stay;
	fsm_table[State::pE1][TransliteratorClass::end] = &ProductionLexer::exit_bad;

	fsm_table[State::pE2][TransliteratorClass::symbol] = &ProductionLexer::E2b;
	fsm_table[State::pE2][TransliteratorClass::quote] = &ProductionLexer::G1a;
	fsm_table[State::pE2][TransliteratorClass::whitespace] = &ProductionLexer::stay;
	fsm_table[State::pE2][TransliteratorClass::end] = &ProductionLexer::exit_bad;

	fsm_table[State::pF1][TransliteratorClass::symbol] = &ProductionLexer::F2a;
	fsm_table[State::pF1][TransliteratorClass::whitespace] = &ProductionLexer::stay;
	fsm_table[State::pF1][TransliteratorClass::end] = &ProductionLexer::exit_bad;

	fsm_table[State::pF2][TransliteratorClass::symbol] = &ProductionLexer::F2b;
	fsm_table[State::pF2][TransliteratorClass::more] = &ProductionLexer::G1a;
	fsm_table[State::pF2][TransliteratorClass::whitespace] = &ProductionLexer::stay;
	fsm_table[State::pF2][TransliteratorClass::end] = &ProductionLexer::exit_bad;

	fsm_table[State::pZ1][TransliteratorClass::symbol] = &ProductionLexer::stay;
	fsm_table[State::pZ1][TransliteratorClass::quote] = &ProductionLexer::stay;
	fsm_table[State::pZ1][TransliteratorClass::less] = &ProductionLexer::stay;
	fsm_table[State::pZ1][TransliteratorClass::more] = &ProductionLexer::stay;
	fsm_table[State::pZ1][TransliteratorClass::colon] = &ProductionLexer::stay;
	fsm_table[State::pZ1][TransliteratorClass::quote] = &ProductionLexer::stay;
	fsm_table[State::pZ1][TransliteratorClass::equals] = &ProductionLexer::stay;
	fsm_table[State::pZ1][TransliteratorClass::whitespace] = &ProductionLexer::stay;
	fsm_table[State::pZ1][TransliteratorClass::newline] = &ProductionLexer::A1b;
	fsm_table[State::pZ1][TransliteratorClass::end] = &ProductionLexer::exit_bad;


	fsm_table[State::pG1][TransliteratorClass::quote] = &ProductionLexer::E1a;
	fsm_table[State::pG1][TransliteratorClass::less] = &ProductionLexer::F1a;
	fsm_table[State::pG1][TransliteratorClass::whitespace] = &ProductionLexer::stay;
	fsm_table[State::pG1][TransliteratorClass::newline] = &ProductionLexer::A1a;
	fsm_table[State::pG1][TransliteratorClass::end] = &ProductionLexer::exit_good;
}


ProductionLexer::~ProductionLexer()
{
}

void ProductionLexer::A1a(TransliteratorToken value)
{
	add_production();
	current_state = State::pA1;
}
void ProductionLexer::A1b(TransliteratorToken value)
{
	current_state = State::pA1;
}
void ProductionLexer::B1a(TransliteratorToken value)
{
	class_register = SymbolClass::Nonterminal;
	current_state = State::pB1;
}
void ProductionLexer::B2a(TransliteratorToken value)
{
	string_register = value.value;
	current_state = State::pB2;
}
void ProductionLexer::B2b(TransliteratorToken value)
{
	string_register += value.value;
	current_state = State::pB2;
}
void ProductionLexer::C1a(TransliteratorToken value)
{
	add_symbol();
	production_register.set_lhs({ bool(class_register), value_register });
	current_state = State::pC1;
}
void ProductionLexer::C2a(TransliteratorToken value)
{
	current_state = State::pC2;
}
void ProductionLexer::C3a(TransliteratorToken value)
{
	current_state = State::pC3;
}
void ProductionLexer::D1a(TransliteratorToken value)
{
	current_state = State::pD1;
}
void ProductionLexer::E1a(TransliteratorToken value)
{
	class_register = SymbolClass::Terminal;
	current_state = State::pE1;
}
void ProductionLexer::E2a(TransliteratorToken value)
{
	string_register = value.value;
	current_state = State::pE2;
}
void ProductionLexer::E2b(TransliteratorToken value)
{
	string_register += value.value;
	current_state = State::pE2;
}
void ProductionLexer::F1a(TransliteratorToken value)
{
	class_register = SymbolClass::Nonterminal;
	current_state = State::pF1;
}
void ProductionLexer::F2a(TransliteratorToken value)
{
	string_register = value.value;
	current_state = State::pF2;
}
void ProductionLexer::F2b(TransliteratorToken value)
{
	string_register += value.value;
	current_state = State::pF2;
}
void ProductionLexer::G1a(TransliteratorToken value)
{
	add_symbol();
	if (string_register != "$")
	{
		production_register.append_rhs({ bool(class_register), value_register });
	}
	current_state = State::pG1;
}
int ProductionLexer::add_symbol()
{
	if (class_register == SymbolClass::Terminal)
	{
		if (string_register == "$")
		{
			return 0;
		}
		int position = find(terminal_symbols_list, string_register);
		if (position == -1)
		{
			terminal_symbols_list.push_back(string_register);
			value_register = terminal_symbols_size;
			++terminal_symbols_size;
		}
		else
		{
			value_register = position;
		}
	}
	else
	{
		int position = find(nonterminal_symbols_list, string_register);
		if (position == -1)
		{
			nonterminal_symbols_list.push_back(string_register);
			value_register = nonterminal_symbols_size;
			++nonterminal_symbols_size;
		}
		else
		{
			value_register = position;
		}
	}
	return 0;
}
void ProductionLexer::add_production()
{
	productions_list.push_back(production_register);
	production_register.clear();
}
void ProductionLexer::error_method(TransliteratorToken value)
{
	error_list.push_back({ current_column, current_row });
}

void ProductionLexer::exit_good(TransliteratorToken value)
{
	if (error_list.empty())
	{
		result = 0;
	}
	result = 1;
}
void ProductionLexer::exit_bad(TransliteratorToken value)
{
	result = 1;
}

int ProductionLexer::find(std::vector<std::string> list, std::string str)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == str)
		{
			return i;
		}
	}
	return -1;
}

TransliteratorToken ProductionLexer::transliterator(char c)
{
	TransliteratorClass value;
	switch (c)
	{
	case '\'':
		value = TransliteratorClass::quote;
		break;
	case '<':
		value = TransliteratorClass::less;
		break;
	case '>':
		value = TransliteratorClass::more;
		break;
	case ':':
		value = TransliteratorClass::colon;
		break;
	case '=':
		value = TransliteratorClass::equals;
		break;
	case ' ': case 9:
		value = TransliteratorClass::whitespace;
		break;
	default:
		value = TransliteratorClass::symbol;
		break;
	}
	return{ value, c };
}

int ProductionLexer::parse_productions(std::string filename)
{
	std::ifstream in(filename);
	std::string line;
	while (std::getline(in, line))
	{
		for (int i = 0; i < line.length(); i++)
		{
			TransliteratorToken tkn = transliterator(line[i]);
			(this->*fsm_table[current_state][tkn.type])(tkn);
			current_column++;
		}
		(this->*fsm_table[current_state][TransliteratorClass::newline])({newline,0});
		current_column = 0;
		current_row++;
	}
	(this->*fsm_table[current_state][TransliteratorClass::end])({ end, 0 });
	in.close();
	return result;
}


std::string ProductionLexer::productions_list_to_string() const
{
	std::string str;
	for each (Production production in productions_list)
	{
		int symbol_index = production.get_lhs().get_value();
		str += "<" + get_nonterminal_symbol(symbol_index) + ">";
		str += " ::= ";
		if (production.get_rhs().empty())
		{
			str += "\'$\'";
		}
		else
		{
			for each (Symbol symbol in production.get_rhs())
			{
				int symbol_index = symbol.get_value();
				bool Terminal = symbol.is_terminal();
				if (Terminal)
				{
					str += "\'" + get_terminal_symbol(symbol_index) + "\'";
				}
				else
				{
					str += "<" + get_nonterminal_symbol(symbol_index) + ">";
				}
				
			}
		}
		str += '\n';
	}
	return str;
}

