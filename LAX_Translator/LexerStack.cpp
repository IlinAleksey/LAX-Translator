#include "LexerStack.h"
#include <cctype>
#include <iostream>
#include <fstream>
#include <stack>
#include <stdlib.h> 
namespace lexr
{
	Lexer::Lexer() :m_fsmTable(LAST_STATE, std::vector<lexerMethod>(LAST, &Lexer::Error))
	{
		m_initVector = {
			-1, -1, -1, -1,
			0,
			-1, -1, -1, -1,
			2,
			-1, -1, -1, -1, -1,
			5,
			-1,
			10,
			-1, -1, -1, -1,
			13,
			-1, -1, -1
		};
		m_transitionTable = { 
			{ 'n', -1, &Lexer::B1b } ,
			{ 'd', -1, &Lexer::C1b },
			{ 'i', 3, &Lexer::E2a },
			{ 'm', -1, &Lexer::B1b },
			{ 'p', -1, &Lexer::E2b },
			{ 'o', 7, &Lexer::B1b },
			{ 'p', -1, &Lexer::E3a },
			{ 'u', -1, &Lexer::B1b },
			{ 's', -1, &Lexer::B1b },
			{ 'h', -1, &Lexer::E1a },
			{ 'e', -1, &Lexer::B1b },
			{ 'a', -1, &Lexer::B1b },
			{ 'd', -1, &Lexer::C1c },
			{ 'r', -1, &Lexer::B1b },
			{ 'i', -1, &Lexer::B1b },
			{ 't', -1, &Lexer::B1b },
			{ 'e', -1, &Lexer::C1d }

		};
		
		m_fsmTable[State::A1][LETTER] = &Lexer::B1a;
		m_fsmTable[State::A1][OP] = &Lexer::C1a;
		m_fsmTable[State::A1][REL] = &Lexer::D1a;
		m_fsmTable[State::A1][SPACE] = &Lexer::A1;
		m_fsmTable[State::A1][CR] = &Lexer::A1;
		m_fsmTable[State::A1][SEMICOLON] = &Lexer::I1a;

		m_fsmTable[State::A2][LETTER] = &Lexer::B1a;
		m_fsmTable[State::A2][OP] = &Lexer::C1a;
		m_fsmTable[State::A2][REL] = &Lexer::D1a;
		m_fsmTable[State::A2][SPACE] = &Lexer::A2;
		m_fsmTable[State::A2][CR] = &Lexer::A2;
		m_fsmTable[State::A2][SEMICOLON] = &Lexer::I2a;
		m_fsmTable[State::A2][END] = &Lexer::EXIT1;

		m_fsmTable[State::B1][LETTER] = &Lexer::M1;

		m_fsmTable[State::C1][SPACE] = &Lexer::C1;
		m_fsmTable[State::C1][CR] = &Lexer::A2;
		m_fsmTable[State::C1][SEMICOLON] = &Lexer::I2a;
		m_fsmTable[State::C1][END] = &Lexer::EXIT1;

		m_fsmTable[State::D1][REL] = &Lexer::C1h;
		m_fsmTable[State::D1][SPACE] = &Lexer::C1g;
		m_fsmTable[State::D1][CR] = &Lexer::A2b;
		m_fsmTable[State::D1][SEMICOLON] = &Lexer::I2a;
		m_fsmTable[State::D1][END] = &Lexer::EXIT2;

		m_fsmTable[State::E1][SPACE] = &Lexer::F1;

		m_fsmTable[State::E2][SPACE] = &Lexer::F2;

		m_fsmTable[State::E3][SPACE] = &Lexer::F3;

		m_fsmTable[State::F1][LETTER] = &Lexer::H1a;
		m_fsmTable[State::F1][DIGIT] = &Lexer::G1a;
		m_fsmTable[State::F1][SPACE] = &Lexer::F1;

		m_fsmTable[State::F2][DIGIT] = &Lexer::G1a;
		m_fsmTable[State::F2][SPACE] = &Lexer::F2;
		
		m_fsmTable[State::F3][LETTER] = &Lexer::H1a;
		m_fsmTable[State::F3][SPACE] = &Lexer::F3;
		
		m_fsmTable[State::G1][DIGIT] = &Lexer::G1b;
		m_fsmTable[State::G1][SPACE] = &Lexer::C1e;
		m_fsmTable[State::G1][CR] = &Lexer::A2c;
		m_fsmTable[State::G1][SEMICOLON] = &Lexer::I2b;
		m_fsmTable[State::G1][END] = &Lexer::EXIT3;

		m_fsmTable[State::H1][LETTER] = &Lexer::H1b;
		m_fsmTable[State::H1][DIGIT] = &Lexer::H1b;
		m_fsmTable[State::H1][SPACE] = &Lexer::C1f;
		m_fsmTable[State::H1][CR] = &Lexer::A2d;
		m_fsmTable[State::H1][SEMICOLON] = &Lexer::I2c;
		m_fsmTable[State::H1][END] = &Lexer::EXIT4;

		m_fsmTable[State::I1][LETTER] = &Lexer::I1;
		m_fsmTable[State::I1][DIGIT] = &Lexer::I1;
		m_fsmTable[State::I1][OP] = &Lexer::I1;
		m_fsmTable[State::I1][REL] = &Lexer::I1;
		m_fsmTable[State::I1][SPACE] = &Lexer::I1;
		m_fsmTable[State::I1][CR] = &Lexer::A1a;
		m_fsmTable[State::I1][SEMICOLON] = &Lexer::I1;
		m_fsmTable[State::I1][ERROR] = &Lexer::I1;

		m_fsmTable[State::I2][LETTER] = &Lexer::I2;
		m_fsmTable[State::I2][DIGIT] = &Lexer::I2;
		m_fsmTable[State::I2][OP] = &Lexer::I2;
		m_fsmTable[State::I2][REL] = &Lexer::I2;
		m_fsmTable[State::I2][SPACE] = &Lexer::I2;
		m_fsmTable[State::I2][CR] = &Lexer::A2b;
		m_fsmTable[State::I2][SEMICOLON] = &Lexer::I2;
		m_fsmTable[State::I2][ERROR] = &Lexer::I2;
		m_fsmTable[State::I2][END] = &Lexer::EXIT1;

		m_fsmTable[State::J1][LETTER] = &Lexer::J1;
		m_fsmTable[State::J1][DIGIT] = &Lexer::J1;
		m_fsmTable[State::J1][OP] = &Lexer::J1;
		m_fsmTable[State::J1][REL] = &Lexer::J1;
		m_fsmTable[State::J1][SPACE] = &Lexer::J1;
		m_fsmTable[State::J1][CR] = &Lexer::A2b;
		m_fsmTable[State::J1][SEMICOLON] = &Lexer::J1;
		m_fsmTable[State::J1][ERROR] = &Lexer::J1;
		m_fsmTable[State::J1][END] = &Lexer::EXIT1;

		isConstant = false;

		m_byteSize = 0;
	}



	Lexer::~Lexer()
	{
	}

	void Lexer::AddLexemeToken()
	{

		switch (m_classRegister)
		{

		case lexr::PUSH:
			m_lexemeList.push_back({ m_classRegister, (int) m_pointerRegister, 5, m_byteSize });
			m_byteSize += 5;
			break;
		case lexr::POP:
			m_lexemeList.push_back({ m_classRegister, (int) m_pointerRegister, 5, m_byteSize });
			m_byteSize += 5;
			break;
		case lexr::OPERATION:
			m_lexemeList.push_back({ m_classRegister, (int) m_valueRegister, 1, m_byteSize });
			m_byteSize += 1;
			break;
		case lexr::RELATION:
			m_lexemeList.push_back({ m_classRegister, (int) m_relationRegister, 1, m_byteSize });
			m_byteSize += 1;
			break;
		case lexr::JUMP:
			m_lexemeList.push_back({ m_classRegister, (int) m_pointerRegister, 5, m_byteSize });
			m_byteSize += 5;
			break;
		case lexr::JUMP_IF:
			m_lexemeList.push_back({ m_classRegister, (int) m_pointerRegister, 5, m_byteSize });
			m_byteSize += 5;
			break;
		case lexr::READ:
			m_lexemeList.push_back({ m_classRegister, 0, 1, m_byteSize });
			m_byteSize += 1;
			break;
		case lexr::WRITE:
			m_lexemeList.push_back({ m_classRegister, 0, 1, m_byteSize });
			m_byteSize += 1;
			break;
		case lexr::END_LEX:
			m_lexemeList.push_back({ m_classRegister, 0, 1, m_byteSize });
			m_byteSize += 1;
			break;
		case lexr::COMMENT:
			//m_lexemeList.push_back({ m_classRegister, 0, 0, m_byteSize });
			m_byteSize += 0;
			break;
		case lexr::ERROR_LEX:
			m_lexemeList.push_back({ m_classRegister, 0, 1, m_byteSize });
			m_byteSize += 1;
			m_correctness = false;
			break;
		case lexr::EXIT_MARKER:
			m_lexemeList.push_back({ m_classRegister, 0, 1, m_byteSize });
			m_byteSize += 1;
			break;
		case lexr::LAST_LEXEMETYPE:
			m_lexemeList.push_back({ m_classRegister,  0, 0, m_byteSize });
			break;
		default:
			break;
		}
	}

	

	void Lexer::AddConstant()
	{
		if (isConstant==true)
		{
			m_pointerRegister = m_constantTable.insert(m_constantRegister.toString(), m_constantRegister);

			isConstant = false;
		}
	}

	int* Lexer::get_constant_pointer(std::string constant)
	{
		return (int*) m_constantTable.insert(constant, LongNumber(constant));
	}

	void Lexer::AddVariable()
	{
		m_pointerRegister = m_variableTable.insert(m_variableRegister, 0);
	}

	State Lexer::A1(SymbolToken symbolToken)
	{
		return State::A1;
	}
	State Lexer::A1a(SymbolToken symbolToken)
	{
		AddLexemeToken();
		return State::A1;
	}
	State Lexer::A2(SymbolToken symbolToken)
	{
		return State::A2;
	}
	State Lexer::A2b(SymbolToken symbolToken)
	{
		AddLexemeToken();
		return State::A2;
	}
	State Lexer::A2c(SymbolToken symbolToken)
	{
		AddConstant();
		AddLexemeToken();
		return State::A2;
	}
	State Lexer::A2d(SymbolToken symbolToken)
	{
		AddVariable();
		AddLexemeToken();
		return State::A2;
	}
	State Lexer::B1(SymbolToken symbolToken)
	{
		return State::B1;
	}
	State Lexer::B1a(SymbolToken symbolToken)
	{
		m_identificationRegister=m_initVector[ symbolToken.value-'a'];
		if (m_identificationRegister==-1)
		{
			return Error(symbolToken);
		}
		return State::B1;
	}
	State Lexer::B1b(SymbolToken symbolToken)
	{
		m_identificationRegister++;
		return State::B1;
	}
	State Lexer::C1(SymbolToken symbolToken)
	{
		return State::C1;
	}
	State Lexer::C1a(SymbolToken symbolToken)
	{
		m_classRegister = LexemeType::OPERATION;
		m_valueRegister = symbolToken.value;
		LexemeToken tmp = { OPERATION, symbolToken.value ,0};
		AddLexemeToken();
		return State::C1;
	}
	
	State Lexer::C1b(SymbolToken symbolToken)
	{
		m_classRegister = LexemeType::END_LEX;

		AddLexemeToken();
		return State::C1;
	}
	State Lexer::C1c(SymbolToken symbolToken)
	{
		m_classRegister = LexemeType::READ;

		AddLexemeToken();
		return State::C1;
	}
	State Lexer::C1d(SymbolToken symbolToken)
	{
		m_classRegister = LexemeType::WRITE;

		AddLexemeToken();
		return State::C1;
	}
	State Lexer::C1e(SymbolToken symbolToken)
	{
		AddConstant();

		AddLexemeToken();
		return State::C1;
	}
	State Lexer::C1f(SymbolToken symbolToken)
	{
		AddVariable();

		AddLexemeToken();
		return State::C1;
	}
	State Lexer::C1g(SymbolToken symbolToken)
	{
		AddLexemeToken();
		return State::C1;
	}
	State Lexer::C1h(SymbolToken symbolToken)
	{
		RelationType newRelationType;
		switch (m_relationRegister)
		{
		case lexr::MORE:
		
			switch (symbolToken.tokenType)
			{
			case EQUAL:
				newRelationType = MOREEQUAL;
				break;
			default:
				newRelationType = LAST_RELATIONTYPE;
				break;
			}
			break;
		case lexr::LESS:
			switch (symbolToken.tokenType)
			{
			case EQUAL:
				newRelationType = LESSEQUAL;
				break;
			default:
				newRelationType = LAST_RELATIONTYPE;
				break;
			}
			break;
		case lexr::EQUAL:
			newRelationType = LAST_RELATIONTYPE;
			break;
		case lexr::NOT:
			switch (symbolToken.tokenType)
			{
			case EQUAL:
				newRelationType = NOTEQUAL;
				break;
			default:
				newRelationType = LAST_RELATIONTYPE;
				break;
			}
			break;
		
		default:
			newRelationType = LAST_RELATIONTYPE;
			break;
		}
		m_relationRegister = newRelationType;
		if (m_relationRegister == LAST_RELATIONTYPE)
		{
			return Error(symbolToken);
		}
		AddLexemeToken();
		return State::C1;
	}
	State Lexer::D1(SymbolToken symbolToken)
	{
		return State::D1;
	}
	State Lexer::D1a(SymbolToken symbolToken)
	{
		m_classRegister = LexemeType::RELATION;
		m_relationRegister = (RelationType)symbolToken.value;
		return State::D1;
	}
	State Lexer::E1(SymbolToken symbolToken)
	{
		return State::E1;
	}
	State Lexer::E1a(SymbolToken symbolToken)
	{
		m_classRegister = LexemeType::PUSH;
		isConstant = true;
		return State::E1;
	}
	State Lexer::E2(SymbolToken symbolToken)
	{
		return State::E2;
	}
	State Lexer::E2a(SymbolToken symbolToken)
	{
		m_classRegister = LexemeType::JUMP_IF;
		isConstant = true;
		return State::E2;
	}
	State Lexer::E2b(SymbolToken symbolToken)
	{
		m_classRegister = LexemeType::JUMP;
		isConstant = true;
		return State::E2;
	}
	State Lexer::E3(SymbolToken symbolToken)
	{
		return State::E3;
	}
	State Lexer::E3a(SymbolToken symbolToken)
	{
		m_classRegister = LexemeType::POP;
		return State::E3;
	}
	State Lexer::F1(SymbolToken symbolToken)
	{
		return State::F1;
	}
	State Lexer::F2(SymbolToken symbolToken)
	{
		return State::F2;
	}
	State Lexer::F3(SymbolToken symbolToken)
	{
		return State::F3;
	}
	
	State Lexer::G1(SymbolToken symbolToken)
	{
		return State::G1;
	}
	State Lexer::G1a(SymbolToken symbolToken)
	{
		m_constantRegister = symbolToken.value;
		return State::G1;
	}
	State Lexer::G1b(SymbolToken symbolToken)
	{
		m_constantRegister.push_back(symbolToken.value);
		
		return State::G1;
	}
	State Lexer::H1(SymbolToken symbolToken)
	{
		return State::H1;
	}
	State Lexer::H1a(SymbolToken symbolToken)
	{
		m_variableRegister = (char)symbolToken.value;
		return State::H1;
	}
	State Lexer::H1b(SymbolToken symbolToken)
	{
		m_variableRegister += (char) symbolToken.value;
		return State::H1;
	}
	State Lexer::I1(SymbolToken symbolToken)
	{
		return State::I1;
	}
	State Lexer::I1a(SymbolToken symbolToken)
	{
		m_classRegister = LexemeType::COMMENT;
		return State::E3;
	}
	State Lexer::I2(SymbolToken symbolToken)
	{
		return State::I2;
	}
	State Lexer::I2a(SymbolToken symbolToken)
	{
		m_classRegister = LexemeType::COMMENT;
		return State::I2;
	}
	State Lexer::I2b(SymbolToken symbolToken)
	{
		AddConstant();
		AddLexemeToken();
		return State::I2;
	}
	State Lexer::I2c(SymbolToken symbolToken)
	{
		AddVariable();
		AddLexemeToken();
		return State::I2;
	}
	State Lexer::J1(SymbolToken symbolToken)
	{
		return State::J1;
	}
	State Lexer::M1(SymbolToken symbolToken)
	{
		while (m_identificationRegister!=-1)
		{
			
			if ((char)symbolToken.value == m_transitionTable[m_identificationRegister].symbol)
			{
				
				return (this->*m_transitionTable[m_identificationRegister].method)(symbolToken);
			}
			else
			{
				m_identificationRegister = m_transitionTable[m_identificationRegister].alternative;
			}
		}
		return Error(symbolToken);
	}
	State Lexer::Error(SymbolToken symbolToken)
	{
		m_classRegister = ERROR_LEX;
		return State::J1;
	}
	State Lexer::EXIT1(SymbolToken symbolToken)
	{
		m_classRegister = EXIT_MARKER;
		AddLexemeToken();
		return State::LAST_STATE;
	}
	State Lexer::EXIT2(SymbolToken symbolToken)
	{
		AddLexemeToken();
		m_classRegister = EXIT_MARKER;
		AddLexemeToken();
		return State::LAST_STATE;
	}
	State Lexer::EXIT3(SymbolToken symbolToken)
	{
		AddConstant();
		AddLexemeToken();
		m_classRegister = EXIT_MARKER;
		AddLexemeToken();
		return State::LAST_STATE;
	}
	State Lexer::EXIT4(SymbolToken symbolToken)
	{
		AddVariable();
		AddLexemeToken();
		m_classRegister = EXIT_MARKER;
		AddLexemeToken();
		return State::LAST_STATE;
	}

	SymbolToken Lexer::Transliterator(char symbol)
	{
		if (isdigit(symbol)!=0)
		{
			return{ SymbolType::DIGIT, (byte)(symbol - '0') };
		}
		if (isalpha(symbol)!=0)
		{
			return{ SymbolType::LETTER, symbol};
		}
		switch (symbol)
		{
		case '+':
			return{ SymbolType::OP, PLUS };
			break;
		case '-':
			return{ SymbolType::OP, MINUS };
			break;
		case '*':
			return{ SymbolType::OP, MULTIPLICATION };
			break;
		case '/':
			return{ SymbolType::OP, DIVISION };
			break;
		case '%':
			return{ SymbolType::OP, MOD };
			break;
		case '>':
			return{ SymbolType::REL, MORE };
			break;
		case '<':
			return{ SymbolType::REL, LESS };
			break;
		case '=':
			return{ SymbolType::REL, EQUAL };
			break;
		case '!':
			return{ SymbolType::REL, NOT };
			break;
		case '\n':
			return{ SymbolType::CR, 0 };
			break;
		case ' ':
			return{ SymbolType::SPACE, 0 };
			break;
		case ';':
			return{ SymbolType::SEMICOLON, 0 };
			break;
		default:
			return{ SymbolType::ERROR, 0 };
			break;
			break;
		}
	}
	void Lexer::Translate(std::string filename)
	{
		std::ifstream myfile(filename);
		/*char temp;
		
		std::string line;*/
		State curState = State::A1;
		char ch;
		while (myfile.get(ch))
		{
			
				SymbolToken token = Transliterator(ch);
				curState = (this->*m_fsmTable[curState][token.tokenType])(token);
			
			
		}
		curState = (this->*m_fsmTable[curState][END])({ SymbolType::END, 0 });
	}
	void Lexer::PrintLexemeList()
	{
		for (std::vector<LexemeToken>::iterator it = m_lexemeList.begin(); it != m_lexemeList.end(); it++)
		{
			std::cout << "(" << (*it).lexemeType << "," << (*it).value << "," << (int)(*it).byteSize << "," << (*it).bytePosition << ")" << std::endl;
		}
		
	}
	std::string Lexer::toByteCode()
	{
		std::ofstream out;
		out.open("binary.dat", std::ios::binary | std::ios::out);

		for (std::vector<LexemeToken>::iterator it = m_lexemeList.begin(); it < m_lexemeList.end(); it++)
		{
			byte lextype;
			int value = (*it).value;
			int address;
			switch ((*it).lexemeType)
			{
			case lexr::PUSH:
				lextype = PUSH_BYTE;
				out.write((char*) &lextype, 1);
				out.write((char*) &value, 4);
				break;
			case lexr::POP:
				lextype = POP_BYTE;
				out.write((char*) &lextype, 1);
				out.write((char*) &value, 4);
				break;
			case lexr::OPERATION:
				switch (value)
				{
				case PLUS:
					lextype = PLUS_BYTE;
					out.write((char*) &lextype, 1);
					break;
				case MINUS:
					lextype = MINUS_BYTE;
					out.write((char*) &lextype, 1);
					break;
				case DIVISION:
					lextype = DIVISION_BYTE;
					out.write((char*) &lextype, 1);
					break;
				case MULTIPLICATION:
					lextype = MULTIPLICATION_BYTE;
					out.write((char*) &lextype, 1);
					break;
				case MOD:
					lextype = MOD_BYTE;
					out.write((char*) &lextype, 1);
					break;
				default:
					break;
				}
				break;
			case lexr::RELATION:
				switch (value)
				{
				case lexr::MORE:
					lextype = MORE_BYTE;
					out.write((char*) &lextype, 1);
					break;
				case lexr::LESS:
					lextype = LESS_BYTE;
					out.write((char*) &lextype, 1);
					break;
				case lexr::EQUAL:
					lextype = EQUAL_BYTE;
					out.write((char*) &lextype, 1);
					break;
				case lexr::NOT:
					break;
				case lexr::NOTEQUAL:
					lextype = NOTEQUAL_BYTE;
					out.write((char*) &lextype, 1);
					break;
				case lexr::MOREEQUAL:
					lextype = MOREEQUAL_BYTE;
					out.write((char*) &lextype, 1);
					break;
				case lexr::LESSEQUAL:
					lextype = LESSEQUAL_BYTE;
					out.write((char*) &lextype, 1);
					break;
				case lexr::LAST_RELATIONTYPE:
					break;
				default:
					break;
				}
				break;
			case lexr::JUMP:
			{
				lextype = JUMP_BYTE;
				out.write((char*) &lextype, 1);
				int lineNumber = (*((LongNumber*) value)).toInt();
				int addressInBytes = m_lexemeList[lineNumber-1].bytePosition;
				out.write((char*) &addressInBytes, 4);

				break;
			}
			case lexr::JUMP_IF:
			{
				lextype = JUMP_IF_BYTE;
				out.write((char*) &lextype, 1);
				int lineNumber = (*((LongNumber*) value)).toInt();
				int addressInBytes = m_lexemeList[lineNumber-1].bytePosition;
				out.write((char*) &addressInBytes, 4);
				break;
			}
			case lexr::READ:
				lextype = READ_BYTE;
				out.write((char*) &lextype, 1);
				break;
			case lexr::WRITE:
				lextype = WRITE_BYTE;
				out.write((char*) &lextype, 1);
				break;
			case lexr::END_LEX:
				lextype = END_LEX_BYTE;
				out.write((char*) &lextype, 1);
				break;
			case lexr::COMMENT:
				break;
			case lexr::ERROR_LEX:
				lextype = ERROR_LEX_BYTE;
				out.write((char*) &lextype, 1);
				break;
			case lexr::EXIT_MARKER:
				lextype = EXIT_MARKER_BYTE;
				out.write((char*) &lextype, 1);
				break;
			case lexr::LAST_LEXEMETYPE:
				break;
			default:
				break;
			}
		}
		return "binary.dat";
	}
	void Lexer::Execute(std::string filename)
	{
		std::ifstream infile;
		infile.open(filename, std::ios::binary | std::ios::in);
		byte lexemeType;
		std::stack<LongNumber> mainStack;
		LongNumber* pointer=new LongNumber;
		while (infile.read((char*)&lexemeType,1))
		{
			//DEBUG
			/*std::cout <<"Lexeme: "<< (int) lexemeType << "\n";
			std::cout << "STACK:\n";
			for (std::stack<LongNumber> dump = mainStack; !dump.empty(); dump.pop())
				std::cout << dump.top() << '\n';
			std::cout << "(" << mainStack.size() << " elements)\n";
			std::cout << '\n';*/
			//

			switch (lexemeType)
			{
			case lexr::PUSH_BYTE:
			{
				LongNumber* pointer = new LongNumber;
				infile.read((char*) &pointer, 4);
				mainStack.push(*pointer);
				break;
			}
			case lexr::POP_BYTE:
			{
				
				LongNumber popped = mainStack.top();
				mainStack.pop();
				infile.read((char*) &pointer, 4);
				
				*pointer = popped;
				
				break;
			}
			case lexr::PLUS_BYTE:
			{
				LongNumber left = mainStack.top();
				mainStack.pop();
				LongNumber right = mainStack.top();
				mainStack.pop();
				LongNumber res = left + right;
				mainStack.push(res);
				break;
			}
			case lexr::MINUS_BYTE:
			{
				LongNumber left = mainStack.top();
				mainStack.pop();
				LongNumber right = mainStack.top();
				mainStack.pop();
				LongNumber res = left - right;
				mainStack.push(res);
				break;
			}
			case lexr::MULTIPLICATION_BYTE:
			{
				LongNumber left = mainStack.top();
				mainStack.pop();
				LongNumber right = mainStack.top();
				mainStack.pop();
				LongNumber res = left * right;
				mainStack.push(res);
				break;
			}
			case lexr::DIVISION_BYTE:
			{
				LongNumber left = mainStack.top();
				mainStack.pop();
				LongNumber right = mainStack.top();
				mainStack.pop();
				LongNumber res = left / right;
				mainStack.push(res);
				break;
			}
			case lexr::MOD_BYTE:
			{
				LongNumber left = mainStack.top();
				mainStack.pop();
				LongNumber right = mainStack.top();
				mainStack.pop();
				LongNumber res = left % right;
				mainStack.push(res);
				break;
			}
			case lexr::MORE_BYTE:
			{
				LongNumber left = mainStack.top();
				mainStack.pop();
				LongNumber right = mainStack.top();
				mainStack.pop();
				LongNumber res = left > right;
				mainStack.push(res);
				break;
			}
			case lexr::LESS_BYTE:
			{
				LongNumber left = mainStack.top();
				mainStack.pop();
				LongNumber right = mainStack.top();
				mainStack.pop();
				LongNumber res = left < right;
				mainStack.push(res);
				break;
			}
			case lexr::EQUAL_BYTE:
			{
				LongNumber left = mainStack.top();
				mainStack.pop();
				LongNumber right = mainStack.top();
				mainStack.pop();
				LongNumber res = left == right;
				mainStack.push(res);
				break;
			}
			case lexr::NOTEQUAL_BYTE:
			{
				LongNumber left = mainStack.top();
				mainStack.pop();
				LongNumber right = mainStack.top();
				mainStack.pop();
				LongNumber res = left != right;
				mainStack.push(res);
				break;
			}
			case lexr::MOREEQUAL_BYTE:
			{
				LongNumber left = mainStack.top();
				mainStack.pop();
				LongNumber right = mainStack.top();
				mainStack.pop();
				LongNumber res = left >= right;
				mainStack.push(res);
				break;
			}
			case lexr::LESSEQUAL_BYTE:
			{
				LongNumber left = mainStack.top();
				mainStack.pop();
				LongNumber right = mainStack.top();
				mainStack.pop();
				LongNumber res = left <= right;
				mainStack.push(res);
				break;
			}
			case lexr::JUMP_BYTE:
			{
				int value=0;
				infile.read((char*) &value, 4);
				infile.seekg(value, std::ios::beg);
				break;
			}
			case lexr::JUMP_IF_BYTE:
			{
				LongNumber popped = mainStack.top();
				mainStack.pop();

				int value;
				infile.read((char*) &value, 4);

				if (popped > 0)
				{
					
					infile.seekg(value, std::ios::beg);
				}

				break;
			}
			case lexr::READ_BYTE:
			{
				LongNumber toPush;
				std::cin >> toPush;
				mainStack.push(toPush);
				break;
			}
			case lexr::WRITE_BYTE:
			{	
				std::cout << mainStack.top()<<std::endl;
				
				break;
			}
				break;
			case lexr::END_LEX_BYTE:
			{
				infile.seekg(0, std::ios::end);
			}
				break;
			case lexr::ERROR_LEX_BYTE:
				break;
			case lexr::EXIT_MARKER_BYTE:
				break;
			case lexr::LAST_BYTE:
				break;
			default:
				break;
			}
		}
	}

	int Lexer::checkErrors()
	{
		int res = 0;
		for (std::vector<LexemeToken>::iterator it = m_lexemeList.begin(); it < m_lexemeList.end(); it++)
		{
			if ((*it).lexemeType==ERROR_LEX)
			{
				std::cout << "Error in line " << std::distance(m_lexemeList.begin(), it)+1 << std::endl;
				res++;
			}
		}
		return res;
	}

	void Lexer::Run(std::string filename)
	{
		Translate(filename);
		PrintLexemeList();
		if (checkErrors()==0)
		{
			std::string byteCodeBinaryFile = toByteCode();
			Execute(byteCodeBinaryFile);
		}
	}
}

