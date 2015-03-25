#include "LongNumber.h"
#include <string>
#include <ctype.h>



LongNumber::LongNumber() :m_number()
{
	
}

LongNumber::LongNumber(int number)
{
	if (number==0)
	{
		m_number.push_back(0);
	}
	else
	{
		for (int temp = std::abs(number); temp > 0; temp /= 10)
		{
			byte rest = temp % 10;
			m_number.push_front(rest);
		}
	}
	
}

LongNumber::LongNumber(std::string str) 
{
	int cur_char = 0;
	
	while (cur_char<str.size())
	{
		if (isdigit(str[cur_char]))
		{
			m_number.push_back(str[cur_char] - '0');
		}
		cur_char++;
		
	}
	Trim();
	
}

LongNumber::LongNumber(const LongNumber& longNumber) :
m_number(lnum(longNumber.m_number))
{

}

LongNumber& LongNumber::Trim()
{

	for (lnum_it it=begin(); (*it)==0 && it!=rbegin(); )
	{
		it++;
		m_number.pop_front();

	}
	return *this;
}

LongNumber& LongNumber::TrimFrom(const lnum_it position)
{
	for (lnum_it it = begin(); (*it) == 0 && it != position;)
	{
		it++;
		m_number.pop_front();

	}
	return *this;
}

void LongNumber::printFrom(const lnum_it position)const
{
	lnum_it it = begin();
	for (; it != position; it++)
	{
		std::cout << int(*it);
	}
	std::cout << int(*it);
}


LongNumber::~LongNumber()
{
}


LongNumber& LongNumber::decr()
{
	byte tosubtract = 1;
	lnum_it it = rbegin();
	for (; tosubtract >0 && it != rend(); it--)
	{

		byte temp = (*it - tosubtract);
		if (temp >= 0)
		{
			(*it)--;
			tosubtract = 0;
		}
		else
		{
			*it = 10 + temp;
			tosubtract = 1;
		}
		
	}
	if (tosubtract>0)
	{
		*this = LongNumber(0);
		return *this;
	}
	else
	{

		return Trim();
	}
	
}

LongNumber& LongNumber::incr()
{
	
	byte toAdd = 1;
	lnum_it it = rbegin();
	for (; toAdd >0 && it != rend(); it--)
	{
		
		byte temp = (*it + toAdd) / 10;
		
		*it=(*it + toAdd) % 10;
		toAdd = temp;
	}
	if (toAdd >0 && (it == rend()))
	{
		m_number.push_front(toAdd);
	}
	
	return *this;
}

LongNumber  LongNumber::add(const LongNumber& _number) const
{
	LongNumber res;
	
	lnum_it it1 = rbegin();
	lnum_it it2 = _number.rbegin();

	byte toAdd = 0;
	for (; it1!=rend() && it2!=_number.rend(); it1--, it2--)
	{
		res.m_number.push_front((*it1 + *it2 + toAdd) % 10);
		toAdd = (*it1 + *it2 + toAdd) / 10;
	}
	for (; it1 != rend(); it1--)
	{
		res.m_number.push_front((*it1 + toAdd) % 10);
		toAdd = (*it1 + toAdd) / 10;
	}
	for (; it2 != _number.rend();  it2--)
	{
		res.m_number.push_front((*it2 + toAdd) % 10);
		toAdd = (*it2 + toAdd) / 10;
	}
	if (toAdd>0)
	{
		res.m_number.push_front( toAdd );
	}
	return res;
}

LongNumber& LongNumber::addFrom(LongNumber& _number, lnum_it position)
{
	
	lnum_it it1 = position;
	lnum_it it2 = _number.rbegin();

	

	byte toAdd = 0;
	for (; it1 != rend() && it2 != _number.rend(); it1--, it2--)
	{
		byte temp_it1 = *it1;
		*it1=((*it1 + *it2 + toAdd) % 10);
		toAdd = (temp_it1 + *it2 + toAdd) / 10;
	}

	for (; it1 != rend(); it1--)
	{
		byte temp_it1 = *it1;
		*it1 = ((*it1 + toAdd) % 10);
		toAdd = (temp_it1 + toAdd) / 10;
	}
	
	for (; it2 != _number.rend(); it2--)
	{
		m_number.push_front((*it2 + toAdd) % 10);
		toAdd = (*it2 + toAdd) / 10;
	}
	
	if (toAdd>0)
	{
		m_number.push_front(toAdd);
	}
	return *this;
}

LongNumber& LongNumber::powerTen(int power)
{
	for (int i = 0; i < power; i++)
	{
		m_number.push_back(0);
	}
	return *this;
}

LongNumber& LongNumber::addFromPower(LongNumber& _number, int power)
{
	addFrom(_number.powerTen(power), rbegin());
	return *this;
}

LongNumber LongNumber::subtract(const LongNumber& _number) const 
{
	LongNumber res;
	
	const LongNumber& left = *this;
	const LongNumber& right = _number;

		
	lnum_it it1 = left.rbegin();
	lnum_it it2 = right.rbegin();

	byte tosubtract = 0;
	for (; it1 != left.rend() && it2 != right.rend(); it1--, it2--)
	{
		byte temp = *it1 - *it2 - tosubtract;

		if (temp >= 0)
		{
			res.m_number.push_front(temp);
			tosubtract = 0;
		}
		else
		{
			res.m_number.push_front((10 + temp) % 10);
			tosubtract = 1;
		}
	}
	for (; it1 != left.rend(); it1--)
	{
		byte temp = *it1 - tosubtract;

		if (temp >= 0)
		{
			res.m_number.push_front(temp);
			tosubtract = 0;
		}
		else
		{
			res.m_number.push_front((10 + temp) % 10);
			tosubtract = 1;
		}
	}

	if (tosubtract>0)
	{
		return LongNumber(0);
	}
	else
	{
		res.Trim();
		return res;
	}
	
}

LongNumber& LongNumber::subtractFrom(LongNumber& _number, lnum_it position)
{
	const LongNumber& left = *this;
	const LongNumber& right = _number;

	lnum_it it1 = position;
	lnum_it it2 = _number.rbegin();

	byte tosubtract = 0;
	for (; it1 != left.rend() && it2 != right.rend(); it1--, it2--)
	{
		byte temp = *it1 - *it2 - tosubtract;

		if (temp >= 0)
		{
			*it1=temp;
			tosubtract = 0;
		}
		else
		{
			*it1 = ((10 + temp) % 10);
			tosubtract = 1;
		}
	}
	for (; it1 != left.rend(); it1--)
	{
		byte temp = *it1 - tosubtract;

		if (temp >= 0)
		{
			*it1=(temp);
			tosubtract = 0;
		}
		else
		{
			*it1 = ((10 + temp) % 10);
			tosubtract = 1;
		}
	}

	if (tosubtract>0)
	{
		return *this = LongNumber(0);
	}
	else
	{
		
		return *this;
	}
}


LongNumber LongNumber::multByDigit(const byte digit) const
{
	if (digit==0)
	{
		return LongNumber(0);
	}
	LongNumber res;

	lnum_it it1 = rbegin();
	
	
	byte toAdd = 0;
	for (; it1 != rend() ; it1--)
	{
		byte temp = (*it1 *digit)+toAdd;
		res.m_number.push_front(temp % 10);
		toAdd = temp / 10;
	}
	if (toAdd>0)
	{
		res.m_number.push_front(toAdd);
	}
	return res;
}

LongNumber LongNumber::mult(const LongNumber& _number) const
{
	if (_number.size()==1)
	{
		return multByDigit(*(_number.rbegin()));
	}

	LongNumber res = 0;
	lnum_it it = _number.rbegin();
	lnum_it it_res = res.rbegin();
	/*for (; it != _number.rend(); it--)
	{
		std::cout << multByDigit(*it) << std::endl;
		res.addFrom(multByDigit(*it), it_res);
		it_res--;
	}*/
	for (int i = 0; i < _number.size(); i++)
	{
		
		res.addFromPower(multByDigit(*it), i);
		it--;
		
	}

	return res;
}

int LongNumber::cmp(const LongNumber& _number) const
{
	int sizecmp = size() - _number.size();
	if (sizecmp != 0)
	{
		return sizecmp;
	}
	lnum_it it1 = begin();
	lnum_it it2 = _number.begin();
	while (it2 != _number.end())
	{

		if ((*it1 - *it2) != 0)
		{
			return *it1 - *it2;
		}
		it2++;
		it1++;
	}
	return 0;
}

int LongNumber::cmpFrom(const LongNumber& _number, const lnum_it position) const
{
	int sizecmp = m_number.range(rend(), position) - _number.size();
	
	if (sizecmp!=0)
	{
		return sizecmp;
	}
	lnum_it it1 = begin();
	lnum_it it2 = _number.begin();
	while (it2!=_number.end())
	{
		
		if ((*it1-*it2)!=0)
		{
			return *it1 - *it2;
		}
		it2++;
		it1++;
	}
	return 0;
}

LongNumber LongNumber::div(const LongNumber& _number) const
{
	

	LongNumber res;
	LongNumber temp = *this;
	lnum_it it = temp.begin();

	while (it != temp.end())
	{
		int digit = 0;
		int cmp = 0;
		while ((cmp = temp.cmpFrom(_number.multByDigit(digit), it)) >= 0)
		{
		
			digit++;
		}
		if (cmp != 0)
		{
			digit--;
		}
		res.m_number.push_back(digit);
		temp.subtractFrom(_number.multByDigit(digit), it);
		

		it++;
		temp.TrimFrom(it);

		
	}

	if (res.size() == 0)
	{
		return LongNumber(0);
	}

	return res.Trim();

	
	


}

LongNumber LongNumber::mod(const LongNumber& _number) const
{
	LongNumber temp = *this;
	lnum_it it = temp.begin();

	while (it != temp.end())
	{
		int digit = 0;
		int cmp = 0;
		while ((cmp = temp.cmpFrom(_number.multByDigit(digit), it)) >= 0)
		{
			
			digit++;
		}
		if (cmp != 0)
		{
			digit--;
		}
		temp.subtractFrom(_number.multByDigit(digit), it);
		

		it++;
		temp.TrimFrom(it);

		
	}

	if (temp.size() == 0)
	{
		return LongNumber(0);
	}

	return temp.Trim();
}




LongNumber& LongNumber::operator++()
{
	return *this;
}
LongNumber& LongNumber::operator--()
{
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& _number)
{
	m_number = _number.m_number;
    return *this;
}

std::string LongNumber::toString()
{
	std::string str;
	for (lnum_it it = begin(); it != end(); it++)
	{
		str += std::to_string(*it);
	}
	return str;
}

LongNumber& LongNumber::push_back(const byte& number)
{
	m_number.push_back(number);
	return *this;
}

LongNumber operator+(const LongNumber& number1, const LongNumber& number2)
{
	return number1.add(number2);

}

LongNumber operator-(const LongNumber& number1, const LongNumber& number2)
{
	return number1.subtract(number2);
}
LongNumber operator*(const LongNumber& number1, const LongNumber& number2)
{
	return number1.mult(number2);
}
LongNumber operator/(const LongNumber& number1, const LongNumber& number2)
{
	return number1.div(number2);
}
LongNumber operator%(const LongNumber& number1, const LongNumber& number2)
{ 
	return number1.mod(number2);
}

bool operator==(const LongNumber& number1, const LongNumber& number2)
{ 
	if (number1.cmp(number2) == 0)
		return true;
	else
		return false;
}
bool operator!=(const LongNumber& number1, const LongNumber& number2)
{ 
	if (number1.cmp(number2) != 0)
		return true;
	else
		return false;
}
bool operator<(const LongNumber& number1, const LongNumber& number2)
{
	if (number1.cmp(number2) < 0)
		return true;
	else
		return false;
}
bool operator>(const LongNumber& number1, const LongNumber& number2)
{ 

	if (number1.cmp(number2) > 0)
		return true;
	else
		return false;
}
bool operator<=(const LongNumber& number1, const LongNumber& number2)
{ 
	
	if (number1.cmp(number2) <= 0)
		return true;
	else
		return false;
}
bool operator>=(const LongNumber& number1, const LongNumber& number2)
{ 
	
	if (number1.cmp(number2) >= 0)
		return true;
	else
		return false;
}

int LongNumber::toInt()
{
	int res = 0;
	for (lnum_it it = begin(); it != end(); it++)
	{
		res = res * 10 + (int) (*it);
	}
	return res;
}

std::ostream& operator<<(std::ostream& out, const LongNumber& longNumber)
{
	for (lnum_it it = longNumber.begin(); it != longNumber.end(); it++)
	{
		out << int(*it);
	}
	return out;
}

std::istream& operator>>(std::istream& in, LongNumber& longNumber)
{
	std::string str;
	in >> str;
	longNumber = LongNumber(str);
	return in;
}
