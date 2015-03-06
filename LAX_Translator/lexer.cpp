#include "lexer.h"
#include <cctype>
#include <iostream>
#include <fstream>
#include <stack>
#include <stdlib.h> 
#include <string>
#include <sstream>

lexer::lexer()
{

}
lexer::~lexer()
{

}
void lexer::add_id()
{
	for (m_current_position;
		m_current_position != m_buffer.end() && isdigit(*m_current_position) || isalpha(*m_current_position);
		m_current_position++)
	{
		m_id_register += *m_current_position;
	}
	m_lexeme_list.push_back({ lexeme_type::ID, NULL });
}

void lexer::Tokenize(std::string filename)
{
	m_current_state = state::A;
	std::ifstream myfile(filename);
	/*char temp;

	std::string line;*/
	std::ifstream t(filename);
	std::stringstream buffer;
	buffer << t.rdbuf();
	m_buffer = buffer.str();
	char ch;

	for (m_current_position = m_buffer.begin(); 
		m_current_position != m_buffer.end();
		)
	{
		switch (*m_current_position)
		{
		case 'h': case 'j': case 'k': case 'l': case 'm': case 'o':
		case 'p': case 'q': case 'r': case 's': case 't': case 'u':
		case 'v': case 'w': case 'x': case 'y': case 'z': case '_':
			add_id();
			break;
		case 'a':
			if (std::distance(m_current_position, m_buffer.end()) >= 1 
				&& m_current_position[1] == 's')
			{
				m_lexeme_list.push_back({ lexeme_type::AS, NULL });
				m_current_position += 2;
			}
			else
			{
				add_id();
			}
		default:
			break;
		}
	}

	myfile.close();
}

void lexer::write_log_file()
{
	std::ofstream log_file("log.txt");
	log_file << m_log_message;
	log_file.close();
}