#include "LLkTableBuilder.h"
#include <exception>
#include <sstream>
LLkTableBuilder::LLkTableBuilder()
{
}

LLkTableBuilder::LLkTableBuilder(int k) : grammar(k)
{

}


LLkTableBuilder::~LLkTableBuilder()
{
}

Sequence LLkTableBuilder::suffix_after_nonterminal(Sequence seq, int index)
{
	return Sequence();
}

std::vector<SequenceSet> LLkTableBuilder::compute_Ysets(const Production& production, const SequenceSet& L) const
{
	std::vector<SequenceSet> result;
	const Sequence& current_sequence = production.get_rhs();
	for (size_t i = 0; i < current_sequence.size(); i++)
	{
		if (!current_sequence[i].is_terminal())
		{
			SequenceSet concatenate = grammar.first(current_sequence.suffix(i + 1));
			concatenate = concatenate.concatenate(L);
			concatenate.truncate(grammar.k);
			result.push_back(concatenate);
		}
	}
	
	return result;
}

void LLkTableBuilder::print_control_table(const llkControlTable& table) const
{
	for each (auto elem in table)
	{
		std::cout << elem.first << '|';
		std::cout << get_productions_list()[elem.second.production_index] << '|';
		std::cout << '{';
		for each (SequenceSet seqset in elem.second.y_sets)
		{
			std::cout << seqset << ',';
		}
		std::cout << '}';
		std::cout << std::endl;
	}
}
std::string LLkTableBuilder::control_table_to_string(const llkControlTable& table) const
{
	std::string to_ret;
	for each (auto elem in table)
	{
		to_ret += grammar.sequence_to_string( elem.first) + "|";
		to_ret += get_productions_list()[elem.second.production_index].production_to_string() + "|";
		to_ret += '{';
		for each (SequenceSet seqset in elem.second.y_sets)
		{
			to_ret += grammar.sequenceset_to_string(seqset) + ",";
		}
		to_ret += "}";
	}
	return to_ret;
}

void LLkTableBuilder::log_control_table(const llkControlTable& table) 
{
	for each (auto elem in table)
	{
		html_logger.AddParagraph(grammar.sequence_to_string(elem.first) + "|" + get_productions_list()[elem.second.production_index].production_to_string() + "| {");

		for each (SequenceSet seqset in elem.second.y_sets)
		{
			html_logger.AddParagraph(grammar.sequenceset_to_string(seqset));
		}
		html_logger.AddParagraph(" ");
	}
}


int LLkTableBuilder::add_control_table(const Symbol& symb, const SequenceSet& seqset, int index)
{
	llkControlTable result;
	int i = 0;
	/*html_logger.AddParagraph(std::to_string(index));
	html_logger.AddParagraph("T " + grammar.symbol_to_string(symb) + ", " + grammar.sequenceset_to_string(seqset) + " = ");*/
	for each (Production production in get_productions_list())
	{
		if (production.get_lhs() == symb)
		{
			SequenceSet first_of_rhs = grammar.first(production.get_rhs());
			/*std::cout << first_of_rhs << std::endl;*/
			SequenceSet conc = first_of_rhs.concatenate(seqset);
			conc.truncate(grammar.k);
			/*std::cout << conc << std::endl;*/
			std::vector<SequenceSet> Y = compute_Ysets(production, seqset);


			for each (Sequence u in conc)
			{
				if (result.find(u) == result.end())
				{
					result[u] = llkControlTableRow{ i, Y };
				}
				else
				{
					return 1;
				}
			}
			
			
		}
		i++;
	}
	control_tables[SymbSeqPair(symb, seqset)] = TableIndexPair(result, index);
	//std::cout << index << " " << symb << " " << seqset << std::endl;
	//print_control_table(result);
	/*log_control_table(result);
	html_logger.SaveFile();*/
	return 0;
}

int LLkTableBuilder::build_control_tables()
{
	grammar.initialize();
	grammar.build_first_sets();
	grammar.debug();

	int current_table_index = 0;

	if (add_control_table(grammar.get_start_symbol(), Sequence(), current_table_index) != NO_CONFLICTS)
	{
		return 1;
	}
	current_table_index++;
	/*control_tables[SymbSeqPair(grammar.get_start_symbol(), Sequence())] = compute_control_table(grammar.get_start_symbol(), Sequence());*/

	/*llkControlTable& initial_table = control_tables[SymbSeqPair(grammar.get_start_symbol(), Sequence())];

	for each (Production production in get_productions_list())
	{
		if (production.get_lhs == grammar.get_start_symbol())
		{
			SequenceSet conc = first(production.get_rhs());
		}
	}*/

	bool stabilized = false;
	while (!stabilized)
	{
		stabilized = true;
		for each (auto table in control_tables)
		{
			llkControlTable& current_table = table.second.first;
			for each (auto row in current_table)
			{
				llkControlTableRow& current_row = row.second;
				const Sequence& current_rhs = get_productions_list()[current_row.production_index].get_rhs();
				int current_index = 0;
				for (size_t i = 0; i < current_rhs.size(); i++)
				{
					if (!current_rhs[i].is_terminal())
					{
						Symbol Bi = current_rhs[i];
						const SequenceSet& Yi = current_row.y_sets[current_index];
						if (control_tables.find(SymbSeqPair(Bi, Yi)) == control_tables.end())
						{
							if (add_control_table(Bi, Yi, current_table_index) != NO_CONFLICTS)
							{
								return 1;
							}
							stabilized = false;
							current_table_index++;
						}
						
						
						current_index++;
					}
				}
			}
		}
	}

	return 0;
}

int LLkTableBuilder::build_oracle()
{
	if (build_control_tables() == 1)
	{
		return 1;
	}
	build_llk_table();
	for each (auto table in control_tables)
	{
		
		const Symbol& table_symbol = table.first.first;
		const SequenceSet& table_sequence_set = table.first.second;

		const llkControlTable& current_table = table.second.first;
		int current_row_index = table.second.second;

		for each (auto row in current_table)
		{
			Sequence temp;
			llkControlTableRow& current_row = row.second;
			const Sequence& current_rhs = get_productions_list()[current_row.production_index].get_rhs();
			int current_index = 0;
			for (size_t i = 0; i < current_rhs.size(); i++)
			{
				if (!current_rhs[i].is_terminal())
				{
					const Symbol& Bi = current_rhs[i];
					const SequenceSet& Yi = current_row.y_sets[current_index];

					int table_index = control_tables.find(SymbSeqPair(Bi, Yi))->second.second;
					temp.push_back(Symbol(SymbolClass::Nonterminal, table_index));
					
					current_index++;
				}
				else
				{
					temp.push_back(current_rhs[i]);
				}
			}
			llk_table[current_row_index][row.first] = LLkTableAction{ LLkTableActionClass::Replace, current_row.production_index, temp };
		}
	}
	build_pop();
	//log_llk_table();
	return 0;
}

int LLkTableBuilder::build_llk_table()
{
	llk_table.resize_control_tables(control_tables.size());
	llk_table.resize_symbol_tables(grammar.terminal_size()+1);
	return 0;
}

int LLkTableBuilder::build_pop()
{
	llk_table[Symbol()][Symbol()] = LLkTableAction{ LLkTableActionClass::Accept, 0, Sequence() };
	return build_pop_helper(Sequence(), 0);
	
}
int LLkTableBuilder::build_pop_helper(Sequence sequence, int position)
{
	if (sequence.size() > grammar.k)
	{
		return 0;
	}
	if (position >= grammar.terminal_size())
	{
		return 0;
	}

	
	
	build_pop_helper(sequence, position + 1);
	Symbol current_symbol = Symbol{ SymbolClass::Terminal, position };
	sequence.push_back(current_symbol);
	build_pop_helper(sequence, 0);
	
	if (sequence.size() <= grammar.k)
	{
		llk_table[*sequence.begin()][sequence] = LLkTableAction{ LLkTableActionClass::Pop, 0, Sequence() };
		/*std::cout << sequence << std::endl;*/
	}
	return 0;
	
}

void LLkTableBuilder::initialize()
{
	build_control_tables();
}

void LLkTableBuilder::pprint_llk_table()
{
	int i = 0;
	for each (auto row in llk_table.control_tables)
	{
		std::cout << "T_" << i << std::endl;
		for each (auto entry in row)
		{
			std::cout << "[";
			grammar.pprint_sequence(entry.first);
			std::cout << " " << entry.second.type << " " << entry.second.value << "] ";
			if (entry.second.sequence.empty())
			{
				std::cout << '$';
			}
			for each (Symbol symb in entry.second.sequence)
			{
				if (symb.is_terminal())
				{
					grammar.pprint_symbol(symb);
					/*std::cout << symb;*/
				}
				else
				{
					std::cout << "<T" << symb.get_value() << ">";
				}
			}
			std::cout << std::endl;

		}
		i++;
	}

}

void LLkTableBuilder::log_llk_table()
{

	int i = 0;
	for each (auto row in llk_table.control_tables)
	{
		html_logger.AddParagraph("T" + std::to_string(i));
		for each (auto entry in row)
		{
			std::string cur;
			cur += "[" + grammar.sequence_to_string(entry.first) + " " + std::to_string(entry.second.type) + " " + std::to_string(entry.second.value) + "] ";
			
			if (entry.second.sequence.empty())
			{
				cur += "$";
			}
			for each (Symbol symb in entry.second.sequence)
			{
				if (symb.is_terminal())
				{
					cur += grammar.symbol_to_string(symb);
					//grammar.pprint_symbol(symb);
					/*std::cout << symb;*/
				}
				else
				{
					cur += "<T" + std::to_string( symb.get_value()) + ">";
				}
			}
			html_logger.AddParagraph(cur);

		}
		i++;
	}
	html_logger.SaveFile();
}

void LLkTableBuilder::serialize(std::string filename)
{
	using namespace tinyxml2;
	XMLDocument xmldoc;
	XMLElement* productions = xmldoc.NewElement("productions");
	xmldoc.InsertEndChild(productions);
	XMLElement* symbols = xmldoc.NewElement("symbols");
	xmldoc.InsertEndChild(symbols);
	XMLElement* oracle = xmldoc.NewElement("oracle");
	xmldoc.InsertEndChild(oracle);

	//productions
	
	//symbols
	XMLElement* terminals = xmldoc.NewElement("terminals");
	symbols->InsertEndChild(terminals);
	XMLElement* nonterminals = xmldoc.NewElement("nonterminals");
	symbols->InsertEndChild(nonterminals);
	for (size_t i = 0; i < grammar.terminal_size(); i++)
	{
		XMLElement* tsymb = xmldoc.NewElement("tsymb");
		tsymb->SetText(grammar.get_terminal_symbol(i).c_str());
		terminals->InsertEndChild(tsymb);
	}
	for (size_t i = 0; i < grammar.nonterminal_size(); i++)
	{
		XMLElement* nsymb = xmldoc.NewElement("nsymb");
		nsymb->SetText(grammar.get_nonterminal_symbol(i).c_str());
		nonterminals->InsertEndChild(nsymb);
	}
	//oracle
	for each (std::unordered_map<Sequence, LLkTableAction> row in llk_table.control_tables)
	{
		XMLElement* row_tag = xmldoc.NewElement("row");
		oracle->InsertEndChild(row_tag);
		for each (auto pair in row)
		{
			const Sequence& sequence = pair.first;
			const LLkTableAction& action = pair.second;

			XMLElement* cell_tag = xmldoc.NewElement("cell");
			row_tag->InsertEndChild(cell_tag);

			//add sequence tag
			XMLElement* sequence_tag = xmldoc.NewElement("sequence");
			for each (Symbol symb in sequence)
			{
				if (symb.is_terminal())
				{
					XMLElement* t = xmldoc.NewElement("t");
					t->SetAttribute("val", symb.get_value());
					sequence_tag->InsertEndChild(t);
				}
				else
				{
					XMLElement* n = xmldoc.NewElement("n");
					n->SetAttribute("val", symb.get_value());
					sequence_tag->InsertEndChild(n);
				}
			}
			cell_tag->InsertEndChild(sequence_tag);

			//add action tag

			XMLElement* action_tag = xmldoc.NewElement("action");
			action_tag->SetAttribute("type", action.type);
			action_tag->SetAttribute("value", action.value);
			for each (Symbol symb in action.sequence)
			{
				if (symb.is_terminal())
				{
					XMLElement* t = xmldoc.NewElement("t");
					t->SetAttribute("val", symb.get_value());
					action_tag->InsertEndChild(t);
				}
				else
				{
					XMLElement* n = xmldoc.NewElement("n");
					n->SetAttribute("val", symb.get_value());
					action_tag->InsertEndChild(n);
				}
			}
			cell_tag->InsertEndChild(action_tag);
		}

	}
	for each (std::unordered_map<Sequence, LLkTableAction> row in llk_table.symbol_tables)
	{
		XMLElement* row_tag = xmldoc.NewElement("row");
		oracle->InsertEndChild(row_tag);
		for each (auto pair in row)
		{
			const Sequence& sequence = pair.first;
			const LLkTableAction& action = pair.second;

			XMLElement* cell_tag = xmldoc.NewElement("cell");
			row_tag->InsertEndChild(cell_tag);

			//add sequence tag
			XMLElement* sequence_tag = xmldoc.NewElement("sequence");
			for each (Symbol symb in sequence)
			{
				if (symb.is_terminal())
				{
					XMLElement* t = xmldoc.NewElement("t");
					t->SetAttribute("val", symb.get_value());
					sequence_tag->InsertEndChild(t);
				}
				else
				{
					XMLElement* n = xmldoc.NewElement("n");
					n->SetAttribute("val", symb.get_value());
					sequence_tag->InsertEndChild(n);
				}
			}
			cell_tag->InsertEndChild(sequence_tag);

			//add action tag

			XMLElement* action_tag = xmldoc.NewElement("action");
			action_tag->SetAttribute("type", action.type);
			action_tag->SetAttribute("value", action.value);
			for each (Symbol symb in action.sequence)
			{
				if (symb.is_terminal())
				{
					XMLElement* t = xmldoc.NewElement("t");
					t->SetAttribute("val", symb.get_value());
					action_tag->InsertEndChild(t);
				}
				else
				{
					XMLElement* n = xmldoc.NewElement("n");
					n->SetAttribute("val", symb.get_value());
					action_tag->InsertEndChild(n);
				}
			}
			cell_tag->InsertEndChild(action_tag);
		}

	}
	xmldoc.SaveFile(filename.c_str());
}