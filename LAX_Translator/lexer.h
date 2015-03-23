#pragma once
#include "LongNumber.h"
#include <vector>
#include <unordered_map>
class lexer;
enum state
{
	A1,A2,A3,B1,C1,D1,E1,F1,G1,H1,K1,I1,J1,T1,ERROR_STATE, LAST_STATE
};
enum transliterator_type
{
	LETTER, DIGIT, PUNCTUATOR, OPERATION, RELATIONSHIP, 
	COLON, ERROR_TYPE, CR, EXIT, LAST_TRANSLITERATOR_TYPE
};
enum operation_type
{ 
	PLUS, MINUS, MULTIPLICATION, DIVISION, MOD, LAST_OPERATION_TYPE 
};
enum relationship_type
{
	MORE, LESS, EQUAL, NOT, GREATER_OR_EQUAL, LESS_OR_EQUAL,
	NOT_EQUAL, EQUAL_EQUAL, LAST_RELATIONSHIP_TYPE
};
enum punctuator_type
{
	SEMICOLON,LEFT_BRACKET,RIGHT_BRACKET
};
enum type_type
{
	INT, LONG
};
enum cr_type
{
	WHITESPACE, NEWLINE, LAST_CR_TYPE
};
enum lexeme_type
{
	ID, CONSTANT, PUNCTUATOR_LEXEME, ASSIGNMENT, OPERATION_LEXEME, TYPE, COLON_LEXEME,
	LABEL, RELATIONSHIP_LEXEME, EMPTY, DIM, AS, FOR, IN, NEXT, IF, THEN, ELSE, INPUT,
	PRINT, GOTO, SWITCH, CASE,
	BREAK, END, FAIL, ERROR_LEXEME, NONE, EXIT_LEXEME,
	LAST_LEXEME_TYPE
};

struct transliterator_token
{
	transliterator_type type;
	char value;
};
struct lexeme_token
{
	lexeme_type type;
	int value;
	std::string id;
};

typedef void(lexer::*lexer_method)(transliterator_token);

struct transition_table_element
{
	char symbol;
	int alternative;
	lexer_method method;
};
class lexer
{
	state m_current_state;
	lexeme_type m_lexeme_type_register;
	void* m_pointer_register;
	LongNumber m_constant_register;
	relationship_type m_relationship_register;
	std::string m_variable_register;
	int m_identification_register;
	int m_value_register;
	int m_right_comment_register;
	bool m_label_register;


	transliterator_token transliterator(char symbol);

	std::vector<lexeme_token> m_lexeme_list;
	void add_lexeme_token();

	std::unordered_map<std::string, LongNumber>m_id_table;

	std::unordered_map<std::string, LongNumber>m_constant_table;

	void add_constant();
	void add_variable();

	std::vector<int> m_init_vector;
	std::vector<transition_table_element> m_transition_table;
	std::vector<transition_table_element> m_in_input_table;

	std::vector<std::vector<lexer_method>> m_fsm_table;

	std::string m_log_message;

	void write_log_file();

	void A1(transliterator_token tkn);
	void A1a(transliterator_token tkn);
	void A1K1(transliterator_token tkn);
	void A1b(transliterator_token tkn);
	void A1c(transliterator_token tkn);
	void A1d(transliterator_token tkn);

	void A2a(transliterator_token tkn);
	void A2b(transliterator_token tkn);

	void A3a(transliterator_token tkn);

	void B1a(transliterator_token tkn);
	void B1b(transliterator_token tkn);

	void C1a(transliterator_token tkn);

	void D1a(transliterator_token tkn);
	void D1b(transliterator_token tkn);

	void E1a(transliterator_token tkn);
	void E1b(transliterator_token tkn);

	void F1a(transliterator_token tkn);

	void G1a(transliterator_token tkn);

	void H1(transliterator_token tkn);
	void H1a(transliterator_token tkn);
	void H1b(transliterator_token tkn);

	void I1a(transliterator_token tkn);
	void I1b(transliterator_token tkn);

	void J1a(transliterator_token tkn);

	void K1a(transliterator_token tkn);
	void K1b(transliterator_token tkn);
	void K1c(transliterator_token tkn);
	void K1d(transliterator_token tkn);
	void K1e(transliterator_token tkn);
	void K1f(transliterator_token tkn);
	void K1g(transliterator_token tkn);
	void K1h(transliterator_token tkn);
	void K1i(transliterator_token tkn);
	void K1j(transliterator_token tkn);
	void K1k(transliterator_token tkn);
	void K1l(transliterator_token tkn);
	void K1m(transliterator_token tkn);
	void K1n(transliterator_token tkn);
	void K1o(transliterator_token tkn);

	void M1(transliterator_token tkn);

	void N1(transliterator_token tkn);

	void T1a(transliterator_token tkn);
	void T1b(transliterator_token tkn);

	void Error(transliterator_token tkn);

	void EXIT1(transliterator_token tkn);
	void EXIT1a(transliterator_token tkn);
	void EXIT1b(transliterator_token tkn);
	void EXIT1c(transliterator_token tkn);
	void EXIT1d(transliterator_token tkn);
	void EXIT1h(transliterator_token tkn);
	void EXIT1n(transliterator_token tkn);

public:
	void Tokenize(std::string filename);
	lexer();
	~lexer();
};

