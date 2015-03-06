#include "lexer.h"
#include <cctype>
#include <iostream>
#include <fstream>
#include <stack>
#include <stdlib.h> 
#include <string>
#include <sstream>

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
		m_current_position++)
	{
		switch (*m_current_position)
		{
		case 'h': case 'j': case 'k': case 'l': case 'm': case 'o':
		case 'p': case 'q': case 'r': case 's': case 't': case 'u':
		case 'v': case 'w': case 'x': case 'y': case 'z':
			m_id_register += *m_current_position
			for (std::string::iterator i = m_current_position;  isdigit(*i) || isalpha(*i)  ; i++)
			{

			}
			break;
		default:
			break;
		}
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