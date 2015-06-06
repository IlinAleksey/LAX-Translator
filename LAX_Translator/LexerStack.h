#pragma once
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Hashtable.h"
#include "LongNumber.h"


namespace lexr
{
	typedef unsigned char byte;
	class Lexer;
	
	enum SymbolType{ LETTER, DIGIT, OP, REL, SPACE, CR, SEMICOLON, ERROR, END, LAST };
	enum LexemeType{ PUSH, POP, OPERATION, RELATION, JUMP, JUMP_IF, READ, WRITE, END_LEX, COMMENT, ERROR_LEX, EXIT_MARKER, LAST_LEXEMETYPE };
	enum OperationType{PLUS,MINUS,MULTIPLICATION,DIVISION,MOD,LAST_OPERATIONTYPE};
	enum RelationType
	{
		MORE,LESS,EQUAL,NOT,NOTEQUAL,MOREEQUAL,LESSEQUAL,LAST_RELATIONTYPE
	};
	enum State{ A1, A2, B1, C1, D1, E1, E2, E3, F1, F2, F3, G1, H1, I1, I2, J1, LAST_STATE };

	enum ByteEncodingType{
		PUSH_BYTE, POP_BYTE, PLUS_BYTE, MINUS_BYTE, MULTIPLICATION_BYTE, DIVISION_BYTE,MOD_BYTE, MORE_BYTE, LESS_BYTE, EQUAL_BYTE, NOTEQUAL_BYTE, MOREEQUAL_BYTE, LESSEQUAL_BYTE, JUMP_BYTE,
		JUMP_IF_BYTE, READ_BYTE, WRITE_BYTE, END_LEX_BYTE, ERROR_LEX_BYTE, EXIT_MARKER_BYTE, LAST_BYTE
	};
	//std::vector<byte> ByteEncondingTypeSize = { 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 1, 1, 1, 1, 1, 1 };
	struct SymbolToken
	{
		SymbolType tokenType;
		int value;
	};

	struct variable
	{
		int value;
	};
	union LexemeValue
	{
		int intValue;
		void* pointer;
	};

	struct LexemeToken
	{
		LexemeType lexemeType;
		unsigned int value;
		byte byteSize;
		unsigned int bytePosition;
	};

	typedef State(Lexer::*lexerMethod)(SymbolToken);

	

	struct transitionTableElements
	{
		char symbol;
		int alternative;
		lexerMethod method;
	};
	

	
	
	class Lexer
	{

		LexemeType m_classRegister;
		void* m_pointerRegister;
		LongNumber m_constantRegister;
		RelationType m_relationRegister;
		std::string m_variableRegister;
		int m_identificationRegister;
		int m_valueRegister;

		bool isConstant;

		bool m_correctness = true;

		std::vector<LexemeToken> m_lexemeList;
		

		int m_byteSize;

		Hashtable m_variableTable;
		Hashtable m_constantTable;
		void AddConstant();
		void AddVariable();

		std::vector<int> m_initVector;
		std::vector<transitionTableElements> m_transitionTable;
		std::vector<std::vector<lexerMethod>> m_fsmTable;

		State A1(SymbolToken symbolToken);
		State A1a(SymbolToken symbolToken);
		State A2(SymbolToken symbolToken);
		State A2b(SymbolToken symbolToken);
		State A2c(SymbolToken symbolToken);
		State A2d(SymbolToken symbolToken);
		State B1(SymbolToken symbolToken);
		State B1a(SymbolToken symbolToken);
		State B1b(SymbolToken symbolToken);
		State C1(SymbolToken symbolToken);
		State C1a(SymbolToken symbolToken);
		State C1b(SymbolToken symbolToken);
		State C1c(SymbolToken symbolToken);
		State C1d(SymbolToken symbolToken);
		State C1e(SymbolToken symbolToken);
		State C1f(SymbolToken symbolToken);
		State C1g(SymbolToken symbolToken);
		State C1h(SymbolToken symbolToken);
		State D1(SymbolToken symbolToken);
		State D1a(SymbolToken symbolToken);
		State E1(SymbolToken symbolToken);
		State E1a(SymbolToken symbolToken);
		State E2(SymbolToken symbolToken);
		State E2a(SymbolToken symbolToken);
		State E2b(SymbolToken symbolToken);
		State E3(SymbolToken symbolToken);
		State E3a(SymbolToken symbolToken);
		State F1(SymbolToken symbolToken);
		State F2(SymbolToken symbolToken);
		State F3(SymbolToken symbolToken);
		State G1(SymbolToken symbolToken);
		State G1a(SymbolToken symbolToken);
		State G1b(SymbolToken symbolToken);
		State H1(SymbolToken symbolToken);
		State H1a(SymbolToken symbolToken);
		State H1b(SymbolToken symbolToken);
		State I1(SymbolToken symbolToken);
		State I1a(SymbolToken symbolToken);
		State I2(SymbolToken symbolToken);
		State I2a(SymbolToken symbolToken);
		State I2b(SymbolToken symbolToken);
		State I2c(SymbolToken symbolToken);
		State J1(SymbolToken symbolToken);
		State M1(SymbolToken symbolToken);
		State Error(SymbolToken symbolToken);
		State EXIT1(SymbolToken symbolToken);
		State EXIT2(SymbolToken symbolToken);
		State EXIT3(SymbolToken symbolToken);
		State EXIT4(SymbolToken symbolToken);

		SymbolToken Transliterator(char symbol);

		int checkErrors();
		
		std::string Debug();
	public:
		Lexer();
		
		~Lexer();
		void Translate(std::string filename);
		std::string toByteCode();
		void Execute(std::string filename);
		void PrintLexemeList();
		const std::vector<LexemeToken>& GetLexemeList()const { return m_lexemeList; }

		void Run(std::string filename);

		void AddPushLexemeByPointer(int* pointer);
		
		void set_is_constant(bool value){ isConstant = value; }
		void set_pointer_register(int* _pointer){ m_pointerRegister = _pointer; }
		void set_constant_register(std::string _variable){ m_constantRegister = _variable; }
		void set_variable_register(std::string _variable){ m_variableRegister = _variable; }
		void set_lexeme_class(LexemeType _class){ m_classRegister = _class; }
		void set_lexeme_value(int _value){ m_valueRegister = _value; }
		void set_relation_register(RelationType _value){ m_relationRegister = _value; }
		void update_value(int index, int value){ m_lexemeList[index].value = value; }
		void AddLexemeToken();
		int* get_constant_pointer(std::string constant);

		
	};
}


