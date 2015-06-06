#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Sequence.h"
enum LLkTableActionClass
{
	Replace, Pop, Accept, Error
};
struct LLkTableAction
{
	LLkTableActionClass type;
	int value;
	Sequence sequence;
};
class LLkTable
{
public:
	std::vector < std::unordered_map<Sequence, LLkTableAction> > control_tables;
	std::vector < std::unordered_map<Sequence, LLkTableAction> > symbol_tables;
	const LLkTableAction& get_action(int table_number, Sequence column) const;
	const LLkTableAction& get_action(Symbol symbol, Sequence column) const;



	LLkTable();
	LLkTable(int control_tables_size, int symbol_tables_size);
	~LLkTable();
	std::unordered_map<Sequence, LLkTableAction>& operator[] (int table_number) { return control_tables[table_number]; }
	const std::unordered_map<Sequence, LLkTableAction>& operator[] (int table_number) const { return control_tables[table_number]; }

	std::unordered_map<Sequence, LLkTableAction>& operator[] (Symbol symbol) 
	{ 
		if (symbol.is_empty())
		{
			return symbol_tables[symbol_tables.size() - 1];
		}
		if (symbol.is_terminal())
		{
			return symbol_tables[symbol.get_value()];
		}
		else
		{
			std::cout << "Not a terminal symbol" << std::endl;
			throw(1);
		}

	}
	const std::unordered_map<Sequence, LLkTableAction>& operator[] (Symbol symbol) const 
	{
		if (symbol.is_terminal())
		{
			return symbol_tables[symbol.get_value()];
		}
		else
		{
			std::cout << "Not a terminal symbol" << std::endl;
			throw(1);
		}
	}

	void resize_control_tables(int new_size) { control_tables.resize(new_size); }
	void resize_symbol_tables(int new_size) { symbol_tables.resize(new_size); }



	friend std::ostream& operator<< (std::ostream& out, const LLkTable& llk_table)
	{
		int i = 0;
		for each (auto row in llk_table.control_tables)
		{
			out << "T_" << i << std::endl;
			for each (auto entry in row)
			{
				out << "[" << entry.first << " " << entry.second.type << " " << entry.second.value << "] ";
				if (entry.second.sequence.empty())
				{
					out << '$';
				}
				for each (Symbol symb in entry.second.sequence)
				{
					if (symb.is_terminal())
					{
						out << symb;
					}
					else
					{
						out << "<T" << symb.get_value() << ">";
					}
				}
				out << std::endl;

			}
			i++;
		}

		return out;

		
	}
};

