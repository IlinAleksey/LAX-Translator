#pragma once
#include <vector>
#include "Symbol.h"
class Sequence
{
	std::vector<Symbol> sequence;
public:
	
	Sequence();
	Sequence(Symbol symb);
	Sequence(std::vector<Symbol> sequence);
	Sequence(std::vector<Symbol>::const_iterator first, std::vector<Symbol>::const_iterator last);
	Sequence& operator=(const Sequence& other){ sequence = other.sequence; return *this; }
	const Sequence& operator=(const Sequence& other) const{ return *this; }
	~Sequence();

	std::vector<Symbol>::iterator begin() { return sequence.begin(); }
	std::vector<Symbol>::const_iterator begin() const { return sequence.begin(); }
	std::vector<Symbol>::iterator end() { return sequence.end(); }
	std::vector<Symbol>::const_iterator end() const { return sequence.end(); }
	void clear() { sequence.clear(); }
	void push_back(const Symbol& val) { sequence.push_back(val); }
	
	bool operator== (const Sequence& other) const { return sequence == other.sequence; }
	bool operator!= (const Sequence& other) const { return sequence != other.sequence; }
	bool operator< (const Sequence& other) const { return sequence < other.sequence; }
	Sequence operator+ (const Sequence& other) const
	{
		if (this->empty())
		{
			return Sequence(other);
		}
		if (other.empty())
		{
			return Sequence(*this);
		}
		Sequence new_seq(*this);
		new_seq.sequence.insert(new_seq.end(), other.begin(), other.end());
		return new_seq;
	}
	Symbol& operator[] (int index) { return sequence[index]; }
	const Symbol& operator[] (int index) const { return sequence[index]; }
	bool empty() const { return sequence.empty() || (size() == 1 && sequence[0] == empty_symbol); }
	size_t size() const { return sequence.size(); }


	void truncate(int length);
	Sequence suffix(const int position) const;


	friend std::ostream& operator<< (std::ostream& out, Sequence sequence)
	{
		if (sequence.empty())
		{
			out << '$';
		}
		for each (Symbol symb in sequence)
		{
			out << symb;
		}
		return out;
	}

};

namespace std {

	template <>
	struct hash < Sequence >
	{
		size_t operator()(const Sequence& k) const
		{

			size_t seed = 0;
			for each (Symbol symb in k)
			{
				seed ^= hash<Symbol>()(symb) +0x9e3779b9 + (seed << 6) + (seed >> 2);

			}
			return seed;
		}
	};

	template <>
	struct hash < pair<Symbol, Sequence> >
	{
		size_t operator()(const pair<Symbol, Sequence>& k) const
		{

			return hash<Symbol>()(k.first) ^ (hash<Sequence>()(k.second) >> 2);
		}
	};

}
