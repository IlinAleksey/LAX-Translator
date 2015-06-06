#include "Sequence.h"


Sequence::Sequence()
{
}

Sequence::Sequence(Symbol symb) : sequence(std::vector < Symbol > {symb})
{

}

Sequence::Sequence(std::vector<Symbol> sequence): sequence(sequence)
{

}

Sequence::Sequence(std::vector<Symbol>::const_iterator first, std::vector<Symbol>::const_iterator last) : sequence(first, last)
{
	
}

Sequence::~Sequence()
{
}

Sequence Sequence::suffix(const int position) const
{
	if (position >= size() || position < 0)
	{
		return Sequence();
	}
	return Sequence(sequence.begin() + position, sequence.end());
}

void Sequence::truncate(int length)
{ 
	if (length < size())
	{
		sequence.resize(length);
	}
	
	return;
}