#pragma once
#include <set>
#include "Sequence.h"
#include "Symbol.h"
class SequenceSet
{
	std::set<Sequence> sequence_set;

public:
	SequenceSet();
	SequenceSet(Sequence);
	SequenceSet(std::set<Sequence>);
	SequenceSet operator=(const SequenceSet& other){ sequence_set = other.sequence_set; return *this; }
	~SequenceSet();

	std::set<Sequence>::iterator begin() { return sequence_set.begin(); }
	std::set<Sequence>::const_iterator begin() const { return sequence_set.begin(); }
	std::set<Sequence>::iterator end() { return sequence_set.end(); }
	std::set<Sequence>::const_iterator end() const { return sequence_set.end(); }

	std::pair<std::set<Sequence>::iterator, bool> insert(const Sequence& sequence) { return sequence_set.insert(sequence); }


	SequenceSet concatenate(const SequenceSet& other) const;
	void truncate(int index);

	SequenceSet union_set(const SequenceSet& other) const;
	SequenceSet intersection_set(SequenceSet other) const;


	bool change(SequenceSet sequence_set);

	bool operator== (const SequenceSet& other) const { return sequence_set == other.sequence_set; }
	bool operator!= (const SequenceSet& other) const { return sequence_set != other.sequence_set; }


	bool empty() const{ return sequence_set.empty(); }

	friend std::ostream& operator<< (std::ostream& out, const SequenceSet& sequence_set)
	{
		out << '{';
		for each (Sequence sequence in sequence_set)
		{
			out << sequence << ',';
		}
		out << '}';
		return out;
	}
};

namespace std {

	template <>
	struct hash < SequenceSet >
	{
		size_t operator()(const SequenceSet& k) const
		{

			size_t seed = 0;
			for each (Sequence seq in k)
			{
				seed ^= hash<Sequence>()(seq) +0x9e3779b9 + (seed << 6) + (seed >> 2);

			}
			return seed;
		}
	};

	template <>
	struct hash < pair<Symbol, SequenceSet> >
	{
		size_t operator()(const pair<Symbol, SequenceSet>& k) const
		{

			return hash<Symbol>()(k.first) ^ (hash<SequenceSet>()(k.second) >> 2);
		}
	};

}