#pragma once
#include "LongNumber.h"
#include <vector>
#include <unordered_map>
class lexer;
enum state
{
	A,B,C,D,E,F,G,H,I,J,K1,K2,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,K14,K15,L,M, N,ERROR_STATE, LAST_STATE
};

enum transliterator_type
{
	DIGIT, LETTER, COLON, SEMICOLON, OPERATION, RELATIONSHIP, CR, ERROR_TYPE,
	EXIT, EQUALITY_SIGN, WHITESPACE, LESS_SIGN, MORE_SIGN, DASH, LEFT_PAR,
	RIGHT_PAR, LAST_TRANSLITERATOR_TYPE
};

enum operation_type{ PLUS, MINUS, MULTIPLICATION, DIVISION, MOD, LAST_OPERATION_TYPE };
enum relationship_type
{
	MORE, LESS, EQUAL, NOT, NOTEQUAL, MOREEQUAL, LESSEQUAL, LAST_RELATIONSHIP_TYPE
};
enum lexeme_type
{
	ID, CONSTANT, EMPTY, DIM, AS, FOR, IN, LEFT_PAR_LEXEME, RIGHT_PAR_LEXEME,
	NEXT, IF, THEN, ELSE, INPUT, PRINT, LABEL, GOTO, SWITCH, CASE,
	BREAK, END, FAIL, ERROR_LEXEME, NONE, EXIT_LEXEME, ASSIGNMENT,
	OPERATION_LEXEME, RELATIONSHIP_LEXEME, LAST_LEXEME_TYPE
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
	lexeme_type m_class_register;
	void* m_pointer_register;
	LongNumber m_constant_register;
	relationship_type m_relation_register;
	std::string m_variable_register;
	int m_identification_register;
	int m_value_register;

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
	void A2(transliterator_token tkn);

	void B1(transliterator_token tkn);
	void B1a(transliterator_token tkn);

	void C1(transliterator_token tkn);
	void C1a(transliterator_token tkn);
	void C1b(transliterator_token tkn);

	void D1(transliterator_token tkn);
	void D1a(transliterator_token tkn);

	void E1(transliterator_token tkn);
	void E1a(transliterator_token tkn);

	void F1(transliterator_token tkn);
	void F1a(transliterator_token tkn);
	void F1_dash(transliterator_token tkn);

	void G1(transliterator_token tkn);

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
	void K14a(transliterator_token tkn);
	void K15a(transliterator_token tkn);

	void I1(transliterator_token tkn);
	void I1a(transliterator_token tkn);

	void L1(transliterator_token tkn);

	void M1(transliterator_token tkn);

	void N1(transliterator_token tkn);
	void N1a(transliterator_token tkn);

	void O1(transliterator_token tkn);

	void Pl(transliterator_token tkn);
	void Pl1(transliterator_token tkn);
	void Pr(transliterator_token tkn);
	void Pr1(transliterator_token tkn);

	void Error(transliterator_token tkn);

	void Exit(transliterator_token tkn);
	void Exit_add_lexeme(transliterator_token tkn);
public:
	void Tokenize(std::string filename);
	lexer();
	~lexer();
};

