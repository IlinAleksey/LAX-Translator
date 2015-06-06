#pragma once
#include "ProductionLexer.h"
#include <set>
#include <unordered_map>
#include "SequenceSet.h"
#include "HtmlLogger.h"
class Grammar
{
	ProductionLexer production_lexer;
	int start_symbol;

	//HtmlLogger grammar_logger;

	std::unordered_map<Symbol, SequenceSet> first_set;
	std::unordered_map<Symbol, SequenceSet> follow_set;
	std::unordered_map<Symbol, SequenceSet> lookahead_set;


	std::unordered_map<Symbol, SequenceSet> begin_set;
	std::unordered_map<Symbol, SequenceSet> end_set;

	
public:
	Grammar();
	Grammar(int k);
	~Grammar();

	int terminal_size() const { return production_lexer.terminal_size(); }
	int nonterminal_size() const { return production_lexer.nonterminal_size(); }
	std::string get_nonterminal_symbol(int index)const{ return production_lexer.get_nonterminal_symbol(index); }
	std::string get_terminal_symbol(int index)const{ return production_lexer.get_terminal_symbol(index); }
	const std::vector<Production>& get_productions_list() const { return production_lexer.get_productions_list(); }

	Symbol get_start_symbol() const { return Symbol{ SymbolClass::Nonterminal, start_symbol }; }

	void build_first_sets();
	void build_follow_sets();
	SequenceSet first(const Sequence& sequence) const;
	SequenceSet follow(const Sequence& sequence) const;

	void initialize();
	void initialize(std::string filename);

	int k;

	void debug()
	{
		std::cout << production_lexer.productions_list_to_string() << std::endl;
		for each (auto elem in first_set)
		{
			std::cout << "FIRST(" << elem.first << ") = " << elem.second << std::endl;
		}
	}

	std::string first_sets_to_string() const;

	void pprint_symbol(const Symbol& symb);
	std::string symbol_to_string(const Symbol& symb) const;
	void pprint_sequence(const Sequence& symb);
	std::string sequence_to_string(const Sequence& symb) const;
	std::string production_to_string(const Production& prod) const;
	std::string sequenceset_to_string(const SequenceSet& symb) const;
};

