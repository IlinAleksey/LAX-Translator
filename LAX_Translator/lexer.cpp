#include "lexer.h"
#include <cctype>
#include <iostream>
#include <fstream>
#include <stack>
#include <stdlib.h> 
#include <string>

std::vector<std::string> state_arr = { 
	"A1", "A2","A3", "B1", "C1", "D1", "E1", "F1", "G1", 
	"H1", "K1", "I1", "J1","T1" "ERROR_STATE", "LAST_STATE" };
std::vector<std::string> lexeme_type_arr = {
	"ID", "CONSTANT", "PUNCTUATOR_LEXEME", "ASSIGNMENT", "OPERATION_LEXEME","TYPE", "COLON_LEXEME",
	"LABEL", 
	"RELATIONSHIP_LEXEME", "EMPTY", "DIM", "AS",
	"FOR", "IN", "NEXT", "IF", "THEN", "ELSE", "INPUT",
	"PRINT",  "GOTO", "SWITCH", "CASE",
	"BREAK", "END", "FAIL", "ERROR_LEXEME", "NONE", "EXIT_LEXEME",
	"LAST_LEXEME_TYPE"
};
std::vector<std::string> transliterator_type_arr = { 
	"LETTER", "DIGIT", "PUNCTUATOR", "OPERATION", "RELATIONSHIP",
	"COLON", "ERROR_TYPE", "CR", "EXIT", "LAST_TRANSLITERATOR_TYPE" };
std::vector<int> right_comment = {cr_type::WHITESPACE, MINUS, MINUS, MORE};
lexer::lexer() :m_fsm_table(LAST_STATE, std::vector<lexer_method>(LAST_TRANSLITERATOR_TYPE, &lexer::Error)),
m_lexeme_type_register(NONE),
m_current_state(state::A1),
m_label_register(false)
{
	m_init_vector = {
		2, //a
		31, //b
		28, //c
		0, //d
		13, //e
		3, //f
		20, //g
		-1,
		5, //i
		-1, -1, 
		40, //l
		-1,
		6, //n
		-1,
		16, //p
		-1, -1,
		23, //s
		10, //t
		-1, -1, -1, -1, -1, -1
	};
	m_transition_table = {
		{ 'i', 43, &lexer::B1b },
		{ 'm', -1, &lexer::K1a },
		{ 's', -1, &lexer::K1b },
		{ 'o', 35, &lexer::B1b },
		{ 'r', -1, &lexer::K1c },
		{ 'n', 9, &lexer::C1a },
		{ 'e', -1, &lexer::B1b },
		{ 'x', -1, &lexer::B1b },
		{ 't', -1, &lexer::K1d },
		{ 'f', -1, &lexer::K1e },
		{ 'h', -1, &lexer::B1b },
		{ 'e', -1, &lexer::B1b },
		{ 'n', -1, &lexer::K1f },
		{ 'l', 38, &lexer::B1b },
		{ 's', -1, &lexer::B1b },
		{ 'e', -1, &lexer::K1g },
		{ 'r', -1, &lexer::B1b },
		{ 'i', -1, &lexer::B1b },
		{ 'n', -1, &lexer::B1b },
		{ 't', -1, &lexer::K1h },
		{ 'o', -1, &lexer::B1b },
		{ 't', -1, &lexer::B1b },
		{ 'o', -1, &lexer::K1i },
		{ 'w', -1, &lexer::B1b },
		{ 'i', -1, &lexer::B1b },
		{ 't', -1, &lexer::B1b },
		{ 'c', -1, &lexer::B1b },
		{ 'h', -1, &lexer::K1j },
		{ 'a', -1, &lexer::B1b },
		{ 's', -1, &lexer::B1b },
		{ 'e', -1, &lexer::K1k },
		{ 'r', -1, &lexer::B1b },
		{ 'e', -1, &lexer::B1b },
		{ 'a', -1, &lexer::B1b },
		{ 'k', -1, &lexer::K1l },
		{ 'a', -1, &lexer::B1b },
		{ 'i', -1, &lexer::B1b },
		{ 'l', -1, &lexer::K1m },
		{ 'n', -1, &lexer::B1b },
		{ 'd', -1, &lexer::K1n },
		{ 'o', -1, &lexer::B1b },
		{ 'n', -1, &lexer::B1b },
		{ 'g', -1, &lexer::T1a },
		{ 'e', -1, &lexer::B1b },
		{ 'f', -1, &lexer::B1b },
		{ 'a', -1, &lexer::B1b },
		{ 'u', -1, &lexer::B1b },
		{ 'l', -1, &lexer::B1b },
		{ 't', -1, &lexer::K1p }

	};
	m_in_input_table = {
		{ 'p', 3, &lexer::D1b },
		{ 'u', -1, &lexer::D1b },
		{ 't', -1, &lexer::K1o },
		{ 't', -1, &lexer::T1b },
	};

	m_fsm_table[state::A1][transliterator_type::LETTER] = &lexer::B1a;
	m_fsm_table[state::A1][transliterator_type::DIGIT] = &lexer::E1a;
	m_fsm_table[state::A1][transliterator_type::PUNCTUATOR] = &lexer::A2a;
	m_fsm_table[state::A1][transliterator_type::OPERATION] = &lexer::A2b;
	m_fsm_table[state::A1][transliterator_type::RELATIONSHIP] = &lexer::F1a;
	m_fsm_table[state::A1][transliterator_type::COLON] = &lexer::A1d;
	m_fsm_table[state::A1][transliterator_type::CR] = &lexer::A1;
	m_fsm_table[state::A1][transliterator_type::EXIT] = &lexer::EXIT1;

	m_fsm_table[state::A2][transliterator_type::CR] = &lexer::A1a;
	m_fsm_table[state::A2][transliterator_type::EXIT] = &lexer::EXIT1a;

	m_fsm_table[state::A3][transliterator_type::LETTER] = &lexer::B1a;
	m_fsm_table[state::A3][transliterator_type::CR] = &lexer::A1a;
	m_fsm_table[state::A3][transliterator_type::EXIT] = &lexer::EXIT1a;

	m_fsm_table[state::B1][transliterator_type::LETTER] = &lexer::M1;
	m_fsm_table[state::B1][transliterator_type::DIGIT] = &lexer::I1a;
	m_fsm_table[state::B1][transliterator_type::CR] = &lexer::A1a;
	m_fsm_table[state::B1][transliterator_type::EXIT] = &lexer::EXIT1a;

	m_fsm_table[state::C1][transliterator_type::LETTER] = &lexer::D1a;
	m_fsm_table[state::C1][transliterator_type::DIGIT] = &lexer::I1a;
	m_fsm_table[state::C1][transliterator_type::CR] = &lexer::A1a;
	m_fsm_table[state::C1][transliterator_type::EXIT] = &lexer::EXIT1a;

	m_fsm_table[state::D1][transliterator_type::LETTER] = &lexer::N1;
	m_fsm_table[state::D1][transliterator_type::DIGIT] = &lexer::I1a;
	m_fsm_table[state::D1][transliterator_type::CR] = &lexer::A1c;
	m_fsm_table[state::D1][transliterator_type::EXIT] = &lexer::EXIT1c;

	m_fsm_table[state::E1][transliterator_type::DIGIT] = &lexer::E1b;
	m_fsm_table[state::E1][transliterator_type::CR] = &lexer::A1a;
	m_fsm_table[state::E1][transliterator_type::EXIT] = &lexer::EXIT1a;

	m_fsm_table[state::F1][transliterator_type::OPERATION] = &lexer::J1a;
	m_fsm_table[state::F1][transliterator_type::RELATIONSHIP] = &lexer::G1a;
	m_fsm_table[state::F1][transliterator_type::CR] = &lexer::A1b;
	m_fsm_table[state::F1][transliterator_type::EXIT] = &lexer::EXIT1b;

	m_fsm_table[state::G1][transliterator_type::CR] = &lexer::A1a;
	m_fsm_table[state::G1][transliterator_type::EXIT] = &lexer::EXIT1a;

	m_fsm_table[state::H1][transliterator_type::LETTER] = &lexer::H1;
	m_fsm_table[state::H1][transliterator_type::DIGIT] = &lexer::H1;
	m_fsm_table[state::H1][transliterator_type::PUNCTUATOR] = &lexer::H1;
	m_fsm_table[state::H1][transliterator_type::OPERATION] = &lexer::H1b;
	m_fsm_table[state::H1][transliterator_type::RELATIONSHIP] = &lexer::H1b;
	m_fsm_table[state::H1][transliterator_type::COLON] = &lexer::H1;
	m_fsm_table[state::H1][transliterator_type::CR] = &lexer::H1b;
	m_fsm_table[state::H1][transliterator_type::EXIT] = &lexer::EXIT1n;

	m_fsm_table[state::J1][transliterator_type::OPERATION] = &lexer::H1a;
	m_fsm_table[state::J1][transliterator_type::EXIT] = &lexer::EXIT1n;

	m_fsm_table[state::I1][transliterator_type::LETTER] = &lexer::I1b;
	m_fsm_table[state::I1][transliterator_type::DIGIT] = &lexer::I1b;
	m_fsm_table[state::I1][transliterator_type::CR] = &lexer::A1a;
	m_fsm_table[state::I1][transliterator_type::EXIT] = &lexer::EXIT1d;

	m_fsm_table[state::K1][transliterator_type::LETTER] = &lexer::I1a;
	m_fsm_table[state::K1][transliterator_type::DIGIT] = &lexer::I1a;
	m_fsm_table[state::K1][transliterator_type::CR] = &lexer::A1c;
	m_fsm_table[state::K1][transliterator_type::EXIT] = &lexer::EXIT1c;

	m_fsm_table[state::ERROR_STATE][transliterator_type::CR] = &lexer::A1a;
	m_fsm_table[state::ERROR_STATE][transliterator_type::EXIT] = &lexer::EXIT1a;
}

lexer::~lexer()
{
}

void lexer::add_lexeme_token()
{
	switch (m_lexeme_type_register)
	{
	case ID:
		m_pointer_register = &m_id_table[m_variable_register];
		m_lexeme_list.push_back({ m_lexeme_type_register, (int) m_pointer_register, m_variable_register });
		break;
	case CONSTANT:
		m_pointer_register = &m_id_table[m_variable_register];
		*(LongNumber*)m_pointer_register = LongNumber(m_variable_register);
		m_lexeme_list.push_back({ m_lexeme_type_register, (int) m_pointer_register, m_variable_register });
		break;
	case OPERATION_LEXEME:
		m_lexeme_list.push_back({ m_lexeme_type_register, m_value_register, "" });
		break;
	case RELATIONSHIP_LEXEME:
		m_lexeme_list.push_back({ m_lexeme_type_register, m_relationship_register, "" });
		break;
	case PUNCTUATOR_LEXEME:
		m_lexeme_list.push_back({ m_lexeme_type_register, m_value_register, "" });
		break;
	case ASSIGNMENT:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case TYPE:
		m_lexeme_list.push_back({ m_lexeme_type_register, m_value_register, "" });
		break;
	case COLON_LEXEME:
		m_lexeme_list.push_back({ m_lexeme_type_register, m_value_register, "" });
		break;
	case LABEL:
		m_pointer_register = &m_id_table[m_variable_register];
		m_lexeme_list.push_back({ 
			m_lexeme_type_register, 
			(int) m_pointer_register, 
			m_variable_register 
		});
		m_label_register = false;
		break;
	case EMPTY:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case DIM:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case AS:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case FOR:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case IN:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case NEXT:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case IF:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case THEN:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case ELSE:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case INPUT:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case PRINT:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case GOTO:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case SWITCH:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case CASE:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case BREAK:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case DEFAULT:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case END:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case FAIL:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case ERROR_LEXEME:
		m_lexeme_list.push_back({ m_lexeme_type_register, m_value_register, "" });
		break;
	case NONE:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	case EXIT_LEXEME:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL });
		break;
	case LAST_LEXEME_TYPE:
		m_lexeme_list.push_back({ m_lexeme_type_register, NULL, "" });
		break;
	default:
		break;
	}
	m_log_message += "\nLexeme added: " + lexeme_type_arr[m_lexeme_type_register]+ "\n";
	m_lexeme_type_register = NONE;
	m_variable_register = "";
	m_value_register = 0;
}



void lexer::A1(transliterator_token tkn)
{
	m_current_state = state::A1;
	return;
}
void lexer::A1a(transliterator_token tkn)
{
	add_lexeme_token();
	m_current_state = state::A1;
	return;
}
void lexer::A1b(transliterator_token tkn)
{
	switch (m_relationship_register)
	{
	case NOT:
		m_current_state = state::ERROR_STATE;
		break;
	case EQUAL:
		m_lexeme_type_register = ASSIGNMENT;
		add_lexeme_token();
		m_current_state = state::A1;
		break;
	default:
		add_lexeme_token();
		m_current_state = state::A1;
		break;
	}
	return;
}
void lexer::A1c(transliterator_token tkn)
{
	
	add_lexeme_token();
	m_current_state = state::A1;
	return;
}
void lexer::A1d(transliterator_token tkn)
{
	/*if (m_label_register)
	{
		m_lexeme_type_register = LABEL;
	}
	add_lexeme_token();
	m_current_state = state::A1;*/
	m_lexeme_type_register = COLON_LEXEME;
	add_lexeme_token();
	m_current_state = state::A1;
	m_label_register = true;
	return;
}
void lexer::A3a(transliterator_token tkn)
{
	m_lexeme_type_register = COLON_LEXEME;
	//m_label_register = true;
	add_lexeme_token();
	m_current_state = state::A1;
	return;
}
void lexer::A2a(transliterator_token tkn)
{
	m_lexeme_type_register = PUNCTUATOR_LEXEME;
	m_value_register = tkn.value;
	m_current_state = state::A2;
	return;
}
void lexer::A2b(transliterator_token tkn)
{
	m_lexeme_type_register = OPERATION_LEXEME;
	m_value_register = tkn.value;
	m_current_state = state::A2;
	return;
}

void lexer::B1a(transliterator_token tkn)
{
	m_lexeme_type_register = ID;
	m_variable_register += tkn.value;
	if (tkn.value <= 'z' && tkn.value >= 'a')
	{
		m_identification_register = tkn.value - 'a';
	}
	else
	{
		m_current_state = state::I1;
		return;
	}
	m_identification_register = m_init_vector[tkn.value - 'a'];
	if (m_identification_register == -1)
	{
		m_current_state = state::I1;
		return;
	}
	else
	{
		m_current_state = state::B1;
		return;
	}
	return;
}
void lexer::B1b(transliterator_token tkn)
{
	m_variable_register += tkn.value;
	m_identification_register++;
	m_current_state = state::B1;
	return;
}
void lexer::C1a(transliterator_token tkn)
{
	m_variable_register += tkn.value;
	m_lexeme_type_register = lexeme_type::IN;
	m_current_state = state::C1;
	return;
}
void lexer::D1a(transliterator_token tkn)
{
	m_identification_register = 0;
	while (m_identification_register != -1)
	{

		if ((char) tkn.value == m_in_input_table[m_identification_register].symbol)
		{

			(this->*m_in_input_table[m_identification_register].method)(tkn);
			return;
		}
		else
		{
			m_identification_register = m_in_input_table[m_identification_register].alternative;
		}
	}
	m_current_state = state::I1;
	return;
}
void lexer::D1b(transliterator_token tkn)
{
	m_variable_register += tkn.value;
	m_identification_register++;
	m_current_state = state::D1;
	return;
}
void lexer::E1a(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::CONSTANT;
	m_variable_register += tkn.value;
	m_current_state = state::E1;
	return;
}
void lexer::E1b(transliterator_token tkn)
{
	m_variable_register += tkn.value;
	m_current_state = state::E1;
	return;
}
void lexer::F1a(transliterator_token tkn)
{
	m_lexeme_type_register = RELATIONSHIP_LEXEME;
	m_relationship_register = (relationship_type) tkn.value;
	m_current_state = state::F1;
	return;
}
void lexer::G1a(transliterator_token tkn)
{
	if (tkn.value == relationship_type::EQUAL)
	{
		switch (m_relationship_register)
		{
		case MORE:
			m_relationship_register = GREATER_OR_EQUAL;
			break;
		case LESS:
			if (tkn.value == relationship_type::EQUAL)
			m_relationship_register = LESS_OR_EQUAL;
			break;
		case EQUAL:
			if (tkn.value == relationship_type::EQUAL)
			m_relationship_register = EQUAL_EQUAL;
			break;
		case NOT:
			if (tkn.value == relationship_type::EQUAL)
			m_relationship_register = NOT_EQUAL;
			break;
		default:
			break;
		}
		m_current_state = G1;
		return;
	}
	m_current_state = ERROR_STATE;
	return;
}
void lexer::J1a(transliterator_token tkn)
{
	if (tkn.value == MINUS)
	{
		m_current_state = J1;
		return;
	}
	m_current_state = ERROR_STATE;
	return;
}
void lexer::H1a(transliterator_token tkn)
{
	if (tkn.value == MINUS)
	{
		m_current_state = state::H1;
		m_right_comment_register = 0;
		return;
	}
	m_current_state = ERROR_STATE;
	return;
}
void lexer::H1(transliterator_token tkn)
{
	m_right_comment_register = 0;
	m_current_state = state::H1;
	return;
}
void lexer::H1b(transliterator_token tkn)
{

	if (tkn.value == right_comment[m_right_comment_register])
	{
		if (m_right_comment_register==right_comment.size()-1)
		{
			m_current_state = state::A1;
		}
		else
		{
			m_right_comment_register++;
			m_current_state = state::H1;
		}
	}
	else
	{
		m_right_comment_register = 0;
	}
	
	return;
}
void lexer::I1a(transliterator_token tkn)
{
	m_lexeme_type_register = ID;
	m_variable_register += tkn.value;
	m_current_state = state::I1;
	return;
}
void lexer::I1b(transliterator_token tkn)
{
	m_variable_register += tkn.value;
	m_current_state = state::I1;
	return;
}
void lexer::K1a(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::DIM;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1b(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::AS;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1c(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::FOR;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1d(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::NEXT;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1e(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::IF;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1f(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::THEN;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1g(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::ELSE;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1h(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::PRINT;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1i(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::GOTO;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1j(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::SWITCH;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1k(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::CASE;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1l(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::BREAK;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1m(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::FAIL;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1n(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::END;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1o(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::INPUT;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::K1p(transliterator_token tkn)
{
	m_lexeme_type_register = lexeme_type::DEFAULT;
	m_variable_register += tkn.value;
	m_current_state = state::K1;
	return;
}
void lexer::M1(transliterator_token tkn)
{
	while (m_identification_register != -1)
	{

		if ((char) tkn.value == m_transition_table[m_identification_register].symbol)
		{

			(this->*m_transition_table[m_identification_register].method)(tkn);
			return;
		}
		else
		{
			m_identification_register = m_transition_table[m_identification_register].alternative;
		}
	}
	m_variable_register += tkn.value;
	m_current_state = state::I1;
	return;
}
void lexer::N1(transliterator_token tkn)
{
	while (m_identification_register != -1)
	{

		if ((char) tkn.value == m_in_input_table[m_identification_register].symbol)
		{

			(this->*m_in_input_table[m_identification_register].method)(tkn);
			return;
		}
		else
		{
			m_identification_register = m_in_input_table[m_identification_register].alternative;
		}
	}
	m_variable_register += tkn.value;
	m_current_state = state::I1;
	return;
}
void lexer::T1a(transliterator_token tkn)
{
	m_current_state = state::K1;
	m_lexeme_type_register = lexeme_type::TYPE;
	m_value_register = type_type::LONG;
	m_variable_register += tkn.value;
	return;
}
void lexer::T1b(transliterator_token tkn)
{
	m_current_state = state::K1;
	m_lexeme_type_register = lexeme_type::TYPE;
	m_value_register = type_type::INT;
	m_variable_register += tkn.value;
	return;
}

void lexer::Error(transliterator_token tkn)
{
	m_current_state = state::ERROR_STATE;
	m_lexeme_type_register = lexeme_type::ERROR_LEXEME;
	return;
}
void lexer::EXIT1(transliterator_token tkn)
{
	return;
}
void lexer::EXIT1a(transliterator_token tkn)
{
	add_lexeme_token();
	return;
}
void lexer::EXIT1b(transliterator_token tkn)
{
	if (tkn.value == NOT)
	{
		m_lexeme_type_register = ERROR_LEXEME;
	}
	add_lexeme_token();
	return;
}
void lexer::EXIT1c(transliterator_token tkn)
{
	add_lexeme_token();
	return;
}
void lexer::EXIT1d(transliterator_token tkn)
{
	
	add_lexeme_token();
	return;
}
void lexer::EXIT1h(transliterator_token tkn)
{
	
	add_lexeme_token();
	return;
}
void lexer::EXIT1n(transliterator_token tkn)
{
	m_lexeme_type_register = ERROR_LEXEME;
	add_lexeme_token();
	return;
}

transliterator_token lexer::transliterator(char symbol)
{
	if (isdigit(symbol) != 0)
	{
		return{ transliterator_type::DIGIT, (byte) (symbol) };
	}
	if (isalpha(symbol) != 0)
	{
		return{ transliterator_type::LETTER, symbol };
	}
	switch (symbol)
	{
	case '+':
		return{ transliterator_type::OPERATION, PLUS };
		break;
	case '-':
		return{ transliterator_type::OPERATION, MINUS };
		break;
	case '*':
		return{ transliterator_type::OPERATION, MULTIPLICATION };
		break;
	case '/':
		return{ transliterator_type::OPERATION, DIVISION };
		break;
	case '%':
		return{ transliterator_type::OPERATION, MOD };
		break;
	case '>':
		return{ transliterator_type::RELATIONSHIP, MORE };
		break;
	case '<':
		return{ transliterator_type::RELATIONSHIP, LESS };
		break;
	case '=':
		return{ transliterator_type::RELATIONSHIP, EQUAL };
		break;
	case '!':
		return{ transliterator_type::RELATIONSHIP, NOT };
		break;
	case '\n':
		return{ transliterator_type::CR, cr_type::NEWLINE };
		break;
	case ' ':
		return{ transliterator_type::CR, cr_type::WHITESPACE };
		break;
	case 9:
		return{ transliterator_type::CR, cr_type::WHITESPACE };
		break;
	case ';':
		return{ transliterator_type::PUNCTUATOR, SEMICOLON };
		break;
	case '(':
		return{ transliterator_type::PUNCTUATOR, LEFT_BRACKET };
		break;
	case ')':
		return{ transliterator_type::PUNCTUATOR, RIGHT_BRACKET };
		break;
	case ':':
		return{ transliterator_type::COLON, 0 };
		break;
	default:
		return{ transliterator_type::ERROR_TYPE, 0 };
		break;
		break;
	}
}

void lexer::Tokenize(std::string filename)
{
	m_current_state = state::A1;
	std::ifstream myfile(filename);
	/*char temp;

	std::string line;*/
	char ch;
	while (myfile.get(ch))
	{

		transliterator_token token = transliterator(ch);
		m_log_message += "Class register: " + lexeme_type_arr[m_lexeme_type_register] + " " + "State: " + state_arr[m_current_state] + " -> ";
		(this->*m_fsm_table[m_current_state][token.type])(token);
		m_log_message += transliterator_type_arr[token.type]+" ";
		m_log_message += "Class register: (" + lexeme_type_arr[m_lexeme_type_register]+" , "+token.value +")"+ " " + "State: " + state_arr[m_current_state] + '\n';
		write_log_file();
	}
	m_log_message += lexeme_type_arr[m_lexeme_type_register] + " " + state_arr[m_current_state] + '\n';
	(this->*m_fsm_table[m_current_state][EXIT])({ transliterator_type::EXIT, 0 });
	m_lexeme_type_register = lexeme_type::EXIT_LEXEME;
	add_lexeme_token();
	write_log_file();
	myfile.close();
}

void lexer::write_log_file()
{
	std::ofstream log_file("log.txt");
	log_file << m_log_message;
	log_file << "Lexeme list:\n";
	for (std::vector<lexeme_token>::iterator i = m_lexeme_list.begin(); i != m_lexeme_list.end(); i++)
	{
		log_file << lexeme_type_arr[(*i).type]<<" "<<(*i).value<<" "<<(*i).id<<'\n';
	}
	log_file.close();
}