#include "lexer.h"
#include <cctype>
#include <iostream>
#include <fstream>
#include <stack>
#include <stdlib.h> 
#include <string>

std::vector<std::string> state_arr = { "A", "B", "C", "D", "E", "F", "G", "H", "H_less", "H_more", "I", "J", "K1", "K2", "K3", "K4", "K5", "K6", "K7", "K8", "K9", "K10", "K11", "K12", "K13", "K14", "K15", "L", "M", "N", "ERROR",
"LAST_STATE" };
std::vector<std::string> lexeme_type_arr = {
	"ID", "CONSTANT", "EMPTY", "DIM", "AS", "FOR", "IN", "LEFT_PAR", "RIGHT_PAR",
	"NEXT", "IF", "THEN", "ELSE", "INPUT", "PRINT", "LABEL", "GOTO", "SWITCH",
	"CASE", "BREAK", "END", "FAIL",
	"ERROR_LEXEME", "NONE", "EXIT_LEXEME", "ASSIGNMENT","OPERATION_LEXEME" ,
	"RELATIONSHIP_LEXEME", "LAST_LEXEME_TYPE"
};
std::vector<std::string> transliterator_type_arr = { 
	"DIGIT", "LETTER", "COLON", "SEMICOLON", "OPERATION", 
	"CR", "ERROR_TYPE", "EXIT", "EQUALITY_SIGN", "WHITESPACE", "LESS_SIGN",
	"MORE_SIGN", "MINUS_SIGN", "LEFT_PAR",
	"RIGHT_PAR","NOT" "LAST_TRANSLITERATOR_TYPE" };
lexer::lexer() :m_fsm_table(LAST_STATE, std::vector<lexer_method>(LAST_TRANSLITERATOR_TYPE, &lexer::Error)),
m_class_register(NONE),
m_current_state(state::A)
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
		-1, -1, -1, -1,
		6, //n
		-1,
		16, //p
		-1, -1,
		24, //s
		10, //t
		-1, -1, -1, -1, -1, -1
	};
	m_transition_table = {
		{ 'i', -1, &lexer::C1a },
		{ 'm', -1, &lexer::K1a },
		{ 's', -1, &lexer::K1b },
		{ 'o', 35, &lexer::C1a },
		{ 'r', -1, &lexer::K1c },
		{ 'n', 9, &lexer::K14a },
		{ 'e', -1, &lexer::C1a },
		{ 'x', -1, &lexer::C1a },
		{ 't', -1, &lexer::K1d },
		{ 'f', -1, &lexer::K1e },
		{ 'h', -1, &lexer::C1a },
		{ 'e', -1, &lexer::C1a },
		{ 'n', -1, &lexer::K1f },
		{ 'l', 38, &lexer::C1a },
		{ 's', -1, &lexer::C1a },
		{ 'e', -1, &lexer::K1g },
		{ 'r', -1, &lexer::C1a },
		{ 'i', -1, &lexer::C1a },
		{ 'n', -1, &lexer::C1a },
		{ 't', -1, &lexer::K1h },
		{ 'o', -1, &lexer::C1a },
		{ 't', -1, &lexer::C1a },
		{ 'o', -1, &lexer::K1i },
		{ 'w', -1, &lexer::C1a },
		{ 'i', -1, &lexer::C1a },
		{ 't', -1, &lexer::C1a },
		{ 'c', -1, &lexer::C1a },
		{ 'h', -1, &lexer::K1j },
		{ 'a', -1, &lexer::C1a },
		{ 's', -1, &lexer::C1a },
		{ 'e', -1, &lexer::K1k },
		{ 'r', -1, &lexer::C1a },
		{ 'e', -1, &lexer::C1a },
		{ 'a', -1, &lexer::C1a },
		{ 'k', -1, &lexer::K1l },
		{ 'a', -1, &lexer::C1a },
		{ 'i', -1, &lexer::C1a },
		{ 'l', -1, &lexer::K1m },
		{ 'n', -1, &lexer::C1a },
		{ 'd', -1, &lexer::K1n },

	};
	m_in_input_table = {
		{ 'p', -1, &lexer::N1a },
		{ 'u', -1, &lexer::N1a },
		{ 't', -1, &lexer::K15a }
	};

	//reading the next symbol, no candidate lexeme yet
	m_fsm_table[state::A][DIGIT] = &lexer::B1;
	m_fsm_table[state::A][LETTER] = &lexer::C1;
	m_fsm_table[state::A][COLON] = &lexer::D1;
	m_fsm_table[state::A][SEMICOLON] = &lexer::E1;
	m_fsm_table[state::A][OPERATION] = &lexer::F1;
	m_fsm_table[state::A][CR] = &lexer::A1;
	m_fsm_table[state::A][ERROR_TYPE] = &lexer::Error;
	m_fsm_table[state::A][EQUALITY_SIGN] = &lexer::G1;
	m_fsm_table[state::A][WHITESPACE] = &lexer::A1;
	m_fsm_table[state::A][LESS_SIGN] = &lexer::E1;
	m_fsm_table[state::A][MORE_SIGN] = &lexer::E1;
	m_fsm_table[state::A][DASH] = &lexer::F1_dash;
	m_fsm_table[state::A][LEFT_PAR] = &lexer::Pl;
	m_fsm_table[state::A][RIGHT_PAR] = &lexer::Pr;
	m_fsm_table[state::A][EXIT] = &lexer::Exit;

	//reading a constant
	m_fsm_table[state::B][DIGIT] = &lexer::B1a;
	m_fsm_table[state::B][LETTER] = &lexer::Error;
	m_fsm_table[state::B][COLON] = &lexer::D1a;
	m_fsm_table[state::B][SEMICOLON] = &lexer::E1a;
	m_fsm_table[state::B][WHITESPACE] = &lexer::A2;
	m_fsm_table[state::B][CR] = &lexer::A2;
	m_fsm_table[state::B][LEFT_PAR] = &lexer::Pl1;
	m_fsm_table[state::B][RIGHT_PAR] = &lexer::Pr1;
	m_fsm_table[state::B][EXIT] = &lexer::Exit_add_lexeme;

	//reading a keyword
	m_fsm_table[state::C][DIGIT] = &lexer::I1;
	m_fsm_table[state::C][LETTER] = &lexer::M1;
	m_fsm_table[state::C][COLON] = &lexer::D1a;
	m_fsm_table[state::C][WHITESPACE] = &lexer::A2;
	m_fsm_table[state::C][CR] = &lexer::A2;
	m_fsm_table[state::C][LEFT_PAR] = &lexer::Pl1;
	m_fsm_table[state::C][RIGHT_PAR] = &lexer::Pr1;
	m_fsm_table[state::C][EXIT] = &lexer::Exit_add_lexeme;

	m_fsm_table[state::G][DIGIT] = &lexer::B1a;
	m_fsm_table[state::G][LETTER] = &lexer::C1b;
	m_fsm_table[state::G][COLON] = &lexer::D1a;
	m_fsm_table[state::G][SEMICOLON] = &lexer::E1a;
	m_fsm_table[state::G][OPERATION] = &lexer::F1a;
	m_fsm_table[state::G][CR] = &lexer::A2;
	m_fsm_table[state::G][ERROR_TYPE] = &lexer::Error;
	m_fsm_table[state::G][EQUALITY_SIGN] = &lexer::H1;
	m_fsm_table[state::G][WHITESPACE] = &lexer::A2;
	m_fsm_table[state::G][LESS_SIGN] = &lexer::H2a;
	m_fsm_table[state::G][MORE_SIGN] = &lexer::H3a;
	m_fsm_table[state::G][DASH] = &lexer::F1_dash;
	m_fsm_table[state::G][LEFT_PAR] = &lexer::Pl1;
	m_fsm_table[state::G][RIGHT_PAR] = &lexer::Pr1;
	m_fsm_table[state::G][EXIT] = &lexer::Exit_add_lexeme;

	m_fsm_table[state::G][DIGIT] = &lexer::B1a;
	m_fsm_table[state::G][LETTER] = &lexer::C1b;
	m_fsm_table[state::G][COLON] = &lexer::D1a;
	m_fsm_table[state::G][SEMICOLON] = &lexer::E1a;
	m_fsm_table[state::G][OPERATION] = &lexer::F1a;
	m_fsm_table[state::G][CR] = &lexer::A2;
	m_fsm_table[state::G][ERROR_TYPE] = &lexer::Error;
	m_fsm_table[state::G][EQUALITY_SIGN] = &lexer::H1;
	m_fsm_table[state::G][WHITESPACE] = &lexer::A2;
	m_fsm_table[state::G][LESS_SIGN] = &lexer::H2a;
	m_fsm_table[state::G][MORE_SIGN] = &lexer::H3a;
	m_fsm_table[state::G][DASH] = &lexer::F1_dash;
	m_fsm_table[state::G][LEFT_PAR] = &lexer::Pl1;
	m_fsm_table[state::G][RIGHT_PAR] = &lexer::Pr1;
	m_fsm_table[state::G][EXIT] = &lexer::Exit_add_lexeme;

	//reading an id
	m_fsm_table[state::I][DIGIT] = &lexer::I1;
	m_fsm_table[state::I][LETTER] = &lexer::I1;
	m_fsm_table[state::I][COLON] = &lexer::D1a;
	m_fsm_table[state::I][SEMICOLON] = &lexer::E1a;
	m_fsm_table[state::I][WHITESPACE] = &lexer::A2;
	m_fsm_table[state::I][CR] = &lexer::I1a;
	m_fsm_table[state::I][LEFT_PAR] = &lexer::Pl1;
	m_fsm_table[state::I][RIGHT_PAR] = &lexer::Pr1;
	m_fsm_table[state::I][EXIT] = &lexer::Exit_add_lexeme;

	//keyword is ready to be added, reading the next symbol
	m_fsm_table[state::K1][DIGIT] = &lexer::I1;
	m_fsm_table[state::K1][LETTER] = &lexer::I1a;
	m_fsm_table[state::K1][COLON] = &lexer::D1a;
	m_fsm_table[state::K1][SEMICOLON] = &lexer::E1a;
	m_fsm_table[state::K1][WHITESPACE] = &lexer::A2;
	m_fsm_table[state::K1][LEFT_PAR] = &lexer::Pl1;
	m_fsm_table[state::K1][RIGHT_PAR] = &lexer::Pr1;
	m_fsm_table[state::K1][EXIT] = &lexer::Exit_add_lexeme;

	//AS is ready to be added, reading the next symbol
	m_fsm_table[state::K2][LETTER] = &lexer::I1a;
	m_fsm_table[state::K2][COLON] = &lexer::D1a;
	m_fsm_table[state::K2][SEMICOLON] = &lexer::E1a;
	m_fsm_table[state::K2][WHITESPACE] = &lexer::A2;
	m_fsm_table[state::K2][EXIT] = &lexer::Exit_add_lexeme;

	//FOR is ready to be added, reading the next symbol
	m_fsm_table[state::K3][LETTER] = &lexer::I1a;
	m_fsm_table[state::K3][COLON] = &lexer::D1a;
	m_fsm_table[state::K3][SEMICOLON] = &lexer::E1a;
	m_fsm_table[state::K3][WHITESPACE] = &lexer::A2;
	m_fsm_table[state::K3][EXIT] = &lexer::Exit_add_lexeme;

	//IN is ready to be added, reading the next symbol
	m_fsm_table[state::K14][LETTER] = &lexer::N1;
	m_fsm_table[state::K14][COLON] = &lexer::D1a;
	m_fsm_table[state::K14][SEMICOLON] = &lexer::E1a;
	m_fsm_table[state::K14][WHITESPACE] = &lexer::A2;
	m_fsm_table[state::K14][EXIT] = &lexer::Exit_add_lexeme;

	//INPUT is ready to be added, reading the next symbol
	m_fsm_table[state::K15][LETTER] = &lexer::I1a;
	m_fsm_table[state::K15][COLON] = &lexer::D1a;
	m_fsm_table[state::K15][SEMICOLON] = &lexer::E1a;
	m_fsm_table[state::K15][WHITESPACE] = &lexer::A2;
	m_fsm_table[state::K15][EXIT] = &lexer::Exit_add_lexeme;

	//reading a possible input keyword
	m_fsm_table[state::N][LETTER] = &lexer::O1;
	m_fsm_table[state::N][COLON] = &lexer::D1a;
	m_fsm_table[state::N][SEMICOLON] = &lexer::E1a;
	m_fsm_table[state::N][WHITESPACE] = &lexer::A2;
	m_fsm_table[state::N][CR] = &lexer::A2;
	m_fsm_table[state::N][EXIT] = &lexer::Exit_add_lexeme;

	//error state: skip all symbols until delimiter
	m_fsm_table[state::ERROR_STATE][LETTER] = &lexer::Error;
	m_fsm_table[state::ERROR_STATE][DIGIT] = &lexer::Error;
	m_fsm_table[state::ERROR_STATE][COLON] = &lexer::D1a;
	m_fsm_table[state::ERROR_STATE][SEMICOLON] = &lexer::E1a;
	m_fsm_table[state::ERROR_STATE][WHITESPACE] = &lexer::A2;
	m_fsm_table[state::ERROR_STATE][CR] = &lexer::A2;
	m_fsm_table[state::ERROR_STATE][EXIT] = &lexer::Exit_add_lexeme;

}

lexer::~lexer()
{
}

void lexer::add_lexeme_token()
{
	switch (m_class_register)
	{
	case ID:
		m_pointer_register = &m_id_table[m_variable_register];
		m_lexeme_list.push_back({ m_class_register, (int)m_pointer_register, m_variable_register });
		break;
	case CONSTANT:
		m_pointer_register = &m_id_table[m_variable_register];
		*(LongNumber*)m_pointer_register = LongNumber(m_variable_register);
		m_lexeme_list.push_back({ m_class_register, (int) m_pointer_register, m_variable_register });
		break;
	case EMPTY:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case DIM:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case AS:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case FOR:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case IN:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case LEFT_PAR_LEXEME:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case RIGHT_PAR_LEXEME:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case NEXT:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case IF:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case THEN:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case ELSE:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case INPUT:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case PRINT:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case LABEL:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case GOTO:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case SWITCH:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case CASE:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case BREAK:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case END:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case FAIL:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case ERROR_LEXEME:
		m_lexeme_list.push_back({ m_class_register, m_value_register, "" });
		break;
	case NONE:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	case EXIT_LEXEME:
		m_lexeme_list.push_back({ m_class_register, NULL });
		break;
	case OPERATION_LEXEME:
		m_lexeme_list.push_back({ m_class_register, m_value_register, "" });
		break;
	case RELATIONSHIP_LEXEME:
		m_lexeme_list.push_back({ m_class_register, m_value_register, "" });
		break;
	case LAST_LEXEME_TYPE:
		m_lexeme_list.push_back({ m_class_register, NULL, "" });
		break;
	default:
		break;
	}
	m_log_message += "Lexeme added: " + lexeme_type_arr[m_class_register];
	m_class_register = NONE;
	m_variable_register = "";
	m_value_register = 0;
}

void lexer::A1(transliterator_token tkn)
{
	m_current_state = state::A;
	return;
}
void lexer::A2(transliterator_token tkn)
{
	add_lexeme_token();
	m_current_state = state::A;
	return;
}
void lexer::B1(transliterator_token tkn)
{
	m_class_register = CONSTANT;
	m_variable_register += tkn.value;
	m_current_state = state::B;
	return;
}
void lexer::B1a(transliterator_token tkn)
{
	m_variable_register += tkn.value;
	m_current_state = state::B;
	return;
}
void lexer::C1(transliterator_token tkn)
{
	m_class_register = ID;
	m_variable_register += tkn.value;
	if (tkn.value <= 'z' && tkn.value >= 'a')
	{
		m_identification_register = tkn.value - 'a';
	}
	else
	{
		m_current_state = state::I;
		return;
	}
	m_identification_register = m_init_vector[tkn.value - 'a'];
	if (m_identification_register == -1)
	{
		m_current_state = state::I;
		return;
	}
	else
	{
		m_current_state = state::C;
		return;
	}
	return;
}
void lexer::C1a(transliterator_token tkn)
{
	m_variable_register += tkn.value;
	m_identification_register++;
	m_current_state = state::C;
	return;
}
void lexer::C1b(transliterator_token tkn)
{
	add_lexeme_token();
	C1(tkn);
	return;
}
void lexer::D1(transliterator_token tkn)
{
	m_class_register = lexeme_type::LABEL;
	add_lexeme_token();
	m_current_state = state::A;
	return;
}
void lexer::D1a(transliterator_token tkn)
{
	add_lexeme_token();
	m_class_register = lexeme_type::LABEL;
	add_lexeme_token();
	m_current_state = state::A;
	return;
}
void lexer::E1(transliterator_token tkn)
{
	m_class_register = EMPTY;
	add_lexeme_token();
	m_current_state = state::A;
	return;
}
void lexer::E1a(transliterator_token tkn)
{
	add_lexeme_token();
	m_class_register = EMPTY;
	add_lexeme_token();
	m_current_state = state::A;
	return;
}
void lexer::F1(transliterator_token tkn)
{
	m_class_register = OPERATION_LEXEME;
	m_value_register = tkn.value;
	add_lexeme_token();
	m_current_state = A;
}
void lexer::F1a(transliterator_token tkn)
{
	add_lexeme_token();
	F1(tkn);
}
void lexer::F1_dash(transliterator_token tkn)
{
	m_class_register = OPERATION_LEXEME;
	m_value_register = operation_type::MINUS;
	add_lexeme_token();
	m_current_state = A;
}
void lexer::G1(transliterator_token tkn)
{
	m_class_register = lexeme_type::ASSIGNMENT;
	m_current_state = G;
}
void lexer::H1(transliterator_token tkn)
{
	m_class_register = lexeme_type::RELATIONSHIP_LEXEME;
	m_value_register = relationship_type::EQUAL;
	m_current_state = H;
}
void lexer::H2(transliterator_token tkn)
{
	m_class_register = lexeme_type::RELATIONSHIP_LEXEME;
	m_value_register = relationship_type::LESS;
	m_current_state = H_LESS;
}
void lexer::H2a(transliterator_token tkn)
{
	add_lexeme_token();
	H2(tkn);
}
void lexer::H3(transliterator_token tkn)
{
	m_class_register = lexeme_type::RELATIONSHIP_LEXEME;
	m_value_register = relationship_type::MORE;
	m_current_state = H_MORE;
}
void lexer::H3a(transliterator_token tkn)
{
	add_lexeme_token();
	H3(tkn);
}
void lexer::I1(transliterator_token tkn)
{
	m_variable_register += tkn.value;
	m_current_state = state::I;
	return;
}
void lexer::I1a(transliterator_token tkn)
{
	m_variable_register += tkn.value;
	add_lexeme_token();
	m_current_state = state::I;
	return;
}
void lexer::K1a(transliterator_token tkn)
{
	m_class_register = lexeme_type::DIM;
	m_current_state = state::K1;
	return;
}
void lexer::K1b(transliterator_token tkn)
{
	m_class_register = lexeme_type::AS;
	m_current_state = state::K1;
	return;
}
void lexer::K1c(transliterator_token tkn)
{
	m_class_register = lexeme_type::FOR;
	m_current_state = state::K1;
	return;
}
void lexer::K1d(transliterator_token tkn)
{
	m_class_register = lexeme_type::NEXT;
	m_current_state = state::K1;
	return;
}
void lexer::K1e(transliterator_token tkn)
{
	m_class_register = lexeme_type::IF;
	m_current_state = state::K1;
	return;
}
void lexer::K1f(transliterator_token tkn)
{
	m_class_register = lexeme_type::THEN;
	m_current_state = state::K1;
	return;
}
void lexer::K1g(transliterator_token tkn)
{
	m_class_register = lexeme_type::ELSE;
	m_current_state = state::K1;
	return;
}
void lexer::K1h(transliterator_token tkn)
{
	m_class_register = lexeme_type::PRINT;
	m_current_state = state::K1;
	return;
}
void lexer::K1i(transliterator_token tkn)
{
	m_class_register = lexeme_type::GOTO;
	m_current_state = state::K1;
	return;
}
void lexer::K1j(transliterator_token tkn)
{
	m_class_register = lexeme_type::SWITCH;
	m_current_state = state::K1;
	return;
}
void lexer::K1k(transliterator_token tkn)
{
	m_class_register = lexeme_type::CASE;
	m_current_state = state::K1;
	return;
}
void lexer::K1l(transliterator_token tkn)
{
	m_class_register = lexeme_type::BREAK;
	m_current_state = state::K1;
	return;
}
void lexer::K1m(transliterator_token tkn)
{
	m_class_register = lexeme_type::FAIL;
	m_current_state = state::K1;
	return;
}
void lexer::K1n(transliterator_token tkn)
{
	m_class_register = lexeme_type::END;
	m_current_state = state::K1;
	return;
}
void lexer::K14a(transliterator_token tkn)
{
	m_class_register = lexeme_type::IN;
	m_current_state = state::K14;
	return;
}
void lexer::K15a(transliterator_token tkn)
{
	m_class_register = lexeme_type::INPUT;
	m_current_state = state::K1;
	return;
}
void lexer::L1(transliterator_token tkn)
{
	m_current_state = state::L;
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
	m_current_state = state::I;
	return;
}
void lexer::N1(transliterator_token tkn)
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
	m_current_state = state::I;
	return;
}
void lexer::N1a(transliterator_token tkn)
{
	m_variable_register += tkn.value;
	m_identification_register++;
	m_current_state = state::N;
	return;
}
void lexer::O1(transliterator_token tkn)
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
	m_current_state = state::I;
	return;
}
void lexer::Pl(transliterator_token tkn)
{
	m_class_register = lexeme_type::LEFT_PAR_LEXEME;
	add_lexeme_token();
	m_current_state = state::A;
	return;
}
void lexer::Pl1(transliterator_token tkn)
{
	add_lexeme_token();
	m_class_register = lexeme_type::LEFT_PAR_LEXEME;
	add_lexeme_token();
	m_current_state = state::A;
	return;
}
void lexer::Pr(transliterator_token tkn)
{
	m_class_register = lexeme_type::RIGHT_PAR_LEXEME;
	add_lexeme_token();
	m_current_state = state::A;
	return;
}
void lexer::Pr1(transliterator_token tkn)
{
	add_lexeme_token();
	m_class_register = lexeme_type::RIGHT_PAR_LEXEME;
	add_lexeme_token();
	m_current_state = state::A;
	return;
}
void lexer::Error(transliterator_token tkn)
{
	m_current_state = state::ERROR_STATE;
	m_class_register = lexeme_type::ERROR_LEXEME;
	return;
}
void lexer::Exit(transliterator_token tkn)
{
	m_class_register = EXIT_LEXEME;
	add_lexeme_token();
	return;
}
void lexer::Exit_add_lexeme(transliterator_token tkn)
{
	add_lexeme_token();
	m_class_register = EXIT_LEXEME;
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
		return{ transliterator_type::DASH, MINUS };
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
		return{ transliterator_type::MORE_SIGN, MORE };
		break;
	case '<':
		return{ transliterator_type::LESS_SIGN, LESS };
		break;
	case '=':
		return{ transliterator_type::EQUALITY_SIGN, 0 };
		break;
	case '!':
		return{ transliterator_type::RELATIONSHIP, NOT };
		break;
	case '\n':
		return{ transliterator_type::CR, 0 };
		break;
	case ' ':
		return{ transliterator_type::WHITESPACE, 0 };
		break;
	case ';':
		return{ transliterator_type::SEMICOLON, 0 };
		break;
	default:
		return{ transliterator_type::ERROR_TYPE, 0 };
		break;
		break;
	}
}

void lexer::Tokenize(std::string filename)
{
	m_current_state = state::A;
	std::ifstream myfile(filename);
	/*char temp;

	std::string line;*/
	char ch;
	while (myfile.get(ch))
	{

		transliterator_token token = transliterator(ch);
		m_log_message += "Class register: " + lexeme_type_arr[m_class_register] + " " + "State: " + state_arr[m_current_state] + " -> ";
		(this->*m_fsm_table[m_current_state][token.type])(token);
		m_log_message += transliterator_type_arr[token.type]+" ";
		m_log_message += "Class register: (" + lexeme_type_arr[m_class_register]+" , "+token.value +")"+ " " + "State: " + state_arr[m_current_state] + '\n';
		write_log_file();
	}
	m_log_message += lexeme_type_arr[m_class_register] + " " + state_arr[m_current_state] + '\n';
	(this->*m_fsm_table[m_current_state][EXIT])({ transliterator_type::EXIT, 0 });
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