#pragma once
#include "LLkTable.h"
#include "Grammar.h"
#include "HtmlLogger.h"
#include "tinyxml2.h"
#define NO_CONFLICTS 0

struct llkControlTableRow
{
	int production_index;
	std::vector<SequenceSet> y_sets;
};

typedef std::unordered_map<Sequence, llkControlTableRow> llkControlTable;
typedef std::pair<Symbol, SequenceSet> SymbSeqPair;

typedef std::pair< llkControlTable, int> TableIndexPair;

class LLkTableBuilder
{
public:
	LLkTable llk_table;
	Grammar grammar;
	bool isLLkGrammar;

	std::unordered_map<std::pair<Symbol, SequenceSet>, std::pair< llkControlTable, int>> control_tables;

	int build_control_tables();
	int build_llk_table();
	int build_pop();
	int build_pop_helper(Sequence sequence, int position);

	Sequence suffix_after_nonterminal(Sequence seq, int index);

	std::vector<SequenceSet> compute_Ysets(const Production& production, const SequenceSet& L) const;

	int add_control_table(const Symbol& symb, const SequenceSet& seqset, int index);

	int build_oracle();


	//public:


	LLkTableBuilder();
	LLkTableBuilder(int k);
	~LLkTableBuilder();

	const std::vector<Production>& get_productions_list() const { return grammar.get_productions_list(); }

	const SequenceSet& first(const Sequence& sequence) const { return grammar.first(sequence); }

	void initialize();

	void print_control_table(const llkControlTable& table) const;
	std::string control_table_to_string(const llkControlTable& table) const;
	void log_control_table(const llkControlTable& table);

	const LLkTable& get_llk_table(){ return llk_table; }

	void pprint_llk_table();
	void log_llk_table();

	HtmlLogger html_logger;

	void serialize(std::string filename);
};

