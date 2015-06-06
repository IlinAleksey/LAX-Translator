#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

enum SymbolClass
{
	Nonterminal, Terminal
};

class Symbol
{
	bool terminal;
	int index;
	
public:
	Symbol() : terminal(true), index(-1){}
	Symbol(bool terminal, int index) : terminal(terminal), index(index){}
	~Symbol();
	bool operator<(const Symbol& other) const
	{
		if (terminal < other.terminal)
		{
			return true;
		}
		else if (terminal > other.terminal)
		{
			return false;
		}
		if (index < other.index)
		{
			return true;
		}
		return false;
	}
	bool operator>(const Symbol& other) const
	{
		if (terminal > other.terminal)
		{
			return true;
		}
		else if (terminal < other.terminal)
		{
			return false;
		}
		if (index > other.index)
		{
			return true;
		}
		return false;
	}

	bool operator<=(const Symbol& other) const
	{
		if (terminal <= other.terminal)
		{
			return true;
		}
		if (index <= other.index)
		{
			return true;
		}
		return false;
	}

	bool operator== (const Symbol& other) const
	{
		return (terminal == other.terminal) && (index == other.index);
	}
	friend std::ostream& operator<< (std::ostream& out, Symbol symbol)
	{
		out << '(' << int(symbol.is_terminal()) << ", " << symbol.get_value() << ')';
		return out;
	}
	bool is_terminal() const{ return terminal; }
	int get_value() const{ return index; }
	SymbolClass get_class() const { return SymbolClass(terminal); }
	bool is_empty() const{ return terminal && index == -1; }
};
const static Symbol empty_symbol = Symbol(1, -1);

namespace std {

	template <>
	struct hash<Symbol>
	{
		std::size_t operator()(const Symbol& k) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			return ((hash<int>()(k.is_terminal() + 1)
				^ (hash<int>()(k.get_value()) << 1)) >> 1);
		}
	};



}

