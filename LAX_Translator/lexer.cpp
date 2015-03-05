#include "lexer.h"
#include <cctype>
#include <iostream>
#include <fstream>
#include <stack>
#include <stdlib.h> 

std::vector<std::string> state_arr = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K1", "K2", "K3", "K4", "K5", "K6", "K7", "K8", "K9", "K10", "K11", "K12", "K13", "K14", "K15", "L", "ERROR",
"LAST_STATE" };
std::vector<std::string> lexeme_type_arr = {
	"EMPTY", "DIM", "AS", "FOR", "IN", "LEFT_PAR", "RIGHT_PAR",
	"NEXT", "IF", "THEN", "ELSE", "INPUT", "PRINT", "LABEL", "GOTO", "SWITCH"
};
lexer::lexer() :m_fsm_table(LAST_STATE, std::vector<lexer_method>(LAST_TRANSLITERATOR_TYPE, &lexer::Error))
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
		24, //s
		10, //t
		-1, -1, -1, -1, -1, -1
	};
	m_transition_table = {
		{ 'i', -1, &lexer::C1a },
		{ 'm', -1, &lexer::K1a },
		{ 's', -1, &lexer::K2a },
		{ 'o', 35, &lexer::C1a },
		{ 'r', -1, &lexer::K3a },
		{ 'n', 9, &lexer::L1 }
	};

	m_fsm_table[state::A][LETTER] = &lexer::C1;

	m_fsm_table[state::C][LETTER] = &lexer::M1;

	m_fsm_table[state::K1][LETTER] = &lexer::K1a;
	m_fsm_table[state::K1][EXIT] = &lexer::Exit_add_lexeme;

}

lexer::~lexer()
{
}

void lexer::add_lexeme_token()
{
	switch (m_class_register)
	{
	case EMPTY:
		break;
	case DIM:
		m_lexeme_list.push_back({m_class_register, NULL	});
		break;
	case AS:
		break;
	case FOR:
		break;
	case IN:
		break;
	case LEFT_PAR:
		break;
	case RIGHT_PAR:
		break;
	case NEXT:
		break;
	case IF:
		break;
	case THEN:
		break;
	case ELSE:
		break;
	case INPUT:
		break;
	case PRINT:
		break;
	case LABEL:
		break;
	case GOTO:
		break;
	case SWITCH:
		break;
	case CASE:
		break;
	case BREAK:
		break;
	case END:
		break;
	case FAIL:
		break;
	case ERROR_LEXEME:
		break;
	case NONE:
		break;
	case EXIT_LEXEME:
		m_lexeme_list.push_back({ m_class_register, NULL });
		break;
	case LAST_LEXEME_TYPE:
		break;
	default:
		break;
	}
}

void lexer::A1(transliterator_token tkn)
{
	return;
}
void lexer::C1(transliterator_token tkn)
{
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
	m_identification_register++;
	m_current_state = state::C;
	return;
}
void lexer::K1a(transliterator_token tkn)
{
	m_class_register = lexeme_type::DIM;
	m_current_state = state::K1;
	return;
}
void lexer::K2a(transliterator_token tkn)
{
	return;
}
void lexer::K3a(transliterator_token tkn)
{
	return;
}
void lexer::L1(transliterator_token tkn)
{
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
	m_current_state = state::ERROR_STATE;
	return;
}
void lexer::Error(transliterator_token tkn)
{
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
		return{ transliterator_type::DIGIT, (byte) (symbol - '0') };
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
		m_log_message += lexeme_type_arr[m_class_register] + " " + state_arr[m_current_state]+'\n';
		(this->*m_fsm_table[m_current_state][token.type])(token);


	}
	m_log_message += lexeme_type_arr[m_class_register] + " " + state_arr[m_current_state] + '\n';
	(this->*m_fsm_table[m_current_state][EXIT])({ transliterator_type::EXIT, 0 });

	myfile.close();
}

void lexer::write_log_file()
{
	std::ofstream log_file("log.txt");
	log_file << m_log_message;
	log_file.close();
}