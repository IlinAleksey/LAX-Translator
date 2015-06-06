#include "Grammar.h"


Grammar::Grammar() : start_symbol(0), k(0)
{
}

Grammar::Grammar(int k) : start_symbol(0), k(k)
{

}

Grammar::~Grammar()
{
}

void Grammar::build_first_sets()
{
	for (size_t i = 0; i < terminal_size(); i++)
	{
		Symbol new_symbol = { bool(SymbolClass::Terminal), int(i) };
		first_set[new_symbol] = SequenceSet(Sequence(new_symbol));
	}
	for (size_t i = 0; i < nonterminal_size(); i++)
	{
		Symbol new_symbol = { bool(SymbolClass::Nonterminal), int(i) };
		first_set[new_symbol] = SequenceSet();
	}
	for each (Production production in get_productions_list())
	{
		if (production.get_rhs().empty())
		{
			first_set[production.get_lhs()].insert(Sequence());
		}
	}
	//grammar_logger.AddParagraph(first_sets_to_string());
	//grammar_logger.SaveFile();
	bool stabilized = false;
	bool not_initialized = false;
	while (!stabilized)
	{
		stabilized = true;
		for each (Production production in get_productions_list())
		{
			//grammar_logger.AddParagraph("Current production: " + production_to_string(production));
			//std::cout << production << std::endl;
			if (!production.get_rhs().empty())
			{
				SequenceSet concatenated;
				for each (Symbol symb in production.get_rhs())
				{
					if (first_set[symb].empty())
					{
						not_initialized = true;
					}
					//grammar_logger.AddParagraph("Concatenate " + sequenceset_to_string(concatenated) + " with " + sequenceset_to_string(first_set[symb]));
					concatenated = concatenated.concatenate(first_set[symb]);
					//grammar_logger.AddParagraph(sequenceset_to_string(concatenated));
					//std::cout << concatenated << std::endl;
				}
				if (not_initialized == false)
				{
					//grammar_logger.AddParagraph("Concatenated: " + sequenceset_to_string(concatenated));
					concatenated.truncate(k);
					//grammar_logger.AddParagraph("Truncated: " + sequenceset_to_string(concatenated));
					//std::cout << concatenated << std::endl;
					SequenceSet new_first_set = concatenated.union_set(first_set[production.get_lhs()]);
					//grammar_logger.AddParagraph("Unionized with " + sequenceset_to_string(first_set[production.get_lhs()]) + ":" + sequenceset_to_string(concatenated));
					if (new_first_set != first_set[production.get_lhs()])
					{

						stabilized = false;
						first_set[production.get_lhs()] = new_first_set;
						//std::cout << "Not stabilized!" << new_first_set << std::endl;
						//grammar_logger.AddParagraph(first_sets_to_string());
						//grammar_logger.SaveFile();
					}
				}
				not_initialized = false;
				
			}
		}
		//std::cout << std::endl;
	}
	

}

void Grammar::build_follow_sets()
{

	Symbol start = { SymbolClass::Nonterminal, start_symbol };
	follow_set[start] = SequenceSet(Sequence());
	for (size_t i = 0; i < nonterminal_size(); i++)
	{
		if (i != start_symbol)
		{
			Symbol new_symbol = { bool(SymbolClass::Nonterminal), int(i) };
			follow_set[new_symbol] = SequenceSet();
		}
	}
	bool stabilized = false;
	while (!stabilized)
	{
		stabilized = true;
		for each (Production production in get_productions_list())
		{
			int rhs_length = production.get_rhs().size();
			SequenceSet L = follow_set[production.get_lhs()];
			Symbol last_symbol_in_production = production.get_rhs()[rhs_length - 1];
			if (last_symbol_in_production.is_terminal() == false)
			{
				SequenceSet FOuL = follow_set[last_symbol_in_production].union_set(L);
				if (FOuL != follow_set[last_symbol_in_production])
				{
					follow_set[last_symbol_in_production] = FOuL;
					stabilized = false;
				}

			}
			for (size_t i = rhs_length-2; i > 0; i--)
			{
				Symbol current_symbol = production.get_rhs()[i];

				L = first_set[current_symbol].concatenate(L);
				L.truncate(k);


				if (current_symbol.is_terminal() == false)
				{
					SequenceSet FOuL = follow_set[current_symbol].union_set(L);
					if (FOuL != follow_set[current_symbol])
					{
						follow_set[current_symbol] = FOuL;
						stabilized = false;
					}

				}
			}
		}
	}
}


SequenceSet Grammar::first(const Sequence& sequence) const
{
	if (sequence.empty())
	{
		return SequenceSet(Sequence());
	}
	SequenceSet concatenated;
	for each (const Symbol symb in sequence)
	{
		std::unordered_map<Symbol, SequenceSet>::const_iterator it = first_set.find(symb);
		concatenated = concatenated.concatenate((*it).second);

	}
	concatenated.truncate(k);
	return concatenated;
}

void Grammar::initialize()
{
	production_lexer.parse_productions("data.txt");
	int a = 2;
	return;
}

void Grammar::initialize(std::string filename)
{
	production_lexer.parse_productions(filename);
}

void Grammar::pprint_symbol(const Symbol& symb)
{
	switch (symb.get_class())
	{
	case Nonterminal:
		std::cout << "<" << get_nonterminal_symbol(symb.get_value()) << ">";
		break;
	case Terminal:
		if (symb.get_value() == -1)
		{
			std::cout << "'$'";
		}
		else
		{
			std::cout << "'" << get_terminal_symbol(symb.get_value()) << "'";
		}
		break;
	default:
		break;
	}
}
void Grammar::pprint_sequence(const Sequence& seq)
{
	if (seq.empty())
	{
		std::cout << "[$]";
		return;
	}
	std::cout << "[";
	for each (Symbol symb in seq)
	{
		pprint_symbol(symb);
	}
	std::cout << "]";
}

std::string Grammar::symbol_to_string(const Symbol& symb) const
{
	std::string result;
	switch (symb.get_class())
	{
	case Nonterminal:
		result = "<" + get_nonterminal_symbol(symb.get_value()) + ">";
		break;
	case Terminal:
		if (symb.get_value() == -1)
		{
			result = "'$'";
		}
		else
		{
			result = "'" + get_terminal_symbol(symb.get_value()) + "'";
		}
		break;
	default:
		break;
	}
	return result;
}
std::string Grammar::sequence_to_string(const Sequence& seq) const
{
	std::string result;
	if (seq.empty())
	{
		result = "[$]";
		return result;
	}
	result+= "[";
	for each (Symbol symb in seq)
	{
		result += symbol_to_string(symb);
	}
	result+= "]";
	return result;
}

std::string Grammar::production_to_string(const Production& prod) const
{
	std::string result;
	result += symbol_to_string(prod.get_lhs());
	result += " ::= ";
	result += sequenceset_to_string(prod.get_rhs());
	return result;
}

std::string Grammar::sequenceset_to_string(const SequenceSet& seqset) const
{
	std::string result;
	if (seqset.empty())
	{
		result = "{$}";
		return result;
	}
	result += "{";
	for each (Sequence symb in seqset)
	{
		result += sequence_to_string(symb);
	}
	result += "}";
	return result;
}

std::string Grammar::first_sets_to_string() const
{
	std::string result;
	for each (auto firstsetpair in first_set)
	{
		result += "FIRST(" + symbol_to_string(firstsetpair.first) + ") = " + sequenceset_to_string(firstsetpair.second) + "\n";
	}
	return result;
}