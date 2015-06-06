#include "SequenceSet.h"
#include <algorithm>
#include <iterator>
SequenceSet::SequenceSet()
{
}


SequenceSet::~SequenceSet()
{
}

SequenceSet::SequenceSet(Sequence sequence) : sequence_set(std::set < Sequence > {sequence})
{

}

SequenceSet::SequenceSet(std::set<Sequence> sequence_set) : sequence_set(sequence_set)
{

}

SequenceSet SequenceSet::concatenate(const SequenceSet& other) const
{
	if (this->sequence_set.empty())
	{
		return other;
	}
	if (other.sequence_set.empty())
	{
		return this->sequence_set;
	}
	std::set<Sequence> result_set;
	for each (Sequence sequence_left in sequence_set)
	{
		for each (Sequence sequence_right in other)
		{
			result_set.insert(sequence_left + sequence_right);
		}
	}
	return SequenceSet(result_set);
}
void SequenceSet::truncate(int index)
{
	SequenceSet new_set;
	for each (Sequence sequence in sequence_set)
	{
		sequence.truncate(index);
		new_set.insert(sequence);
	}
	*this = new_set;
	/*std::for_each(sequence_set.begin(), sequence_set.end(), [index](Sequence& sequence){sequence.truncate(index); });*/
}

SequenceSet SequenceSet::union_set(const SequenceSet& other)const
{
	SequenceSet new_sequence_set;

	/*std::set<Sequence>::iterator it = new_sequence_set.begin();*/
	std::set_union(begin(), end(), other.begin(), other.end(), std::inserter(new_sequence_set.sequence_set, new_sequence_set.begin()));
	return new_sequence_set;
}
SequenceSet SequenceSet::intersection_set(SequenceSet other) const
{
	SequenceSet new_sequence_set;
	return new_sequence_set;
}

bool SequenceSet::change(SequenceSet sequence_set)
{
	return true;
}
