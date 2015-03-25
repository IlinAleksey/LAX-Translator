#pragma once
#include "dlist.h"
#include <iostream>
#include <ostream>

typedef char byte;
typedef dlst::dlist<byte> lnum;
typedef dlst::iterator<byte> lnum_it;



class LongNumber
{
protected:
	lnum m_number;


	LongNumber& decr();
	LongNumber& incr();
	LongNumber abs() const;
	LongNumber add(const LongNumber& _number) const;
	LongNumber& addFrom(LongNumber& _number, lnum_it position);
	LongNumber& addFromPower(LongNumber& _number, int power);
	LongNumber subtract(const LongNumber& _number) const;
	LongNumber& subtractFrom(LongNumber& _number, lnum_it position);
	LongNumber multByDigit(const byte digit) const;
	LongNumber mult(const LongNumber& _number) const;
	LongNumber div(const LongNumber& _number) const;
	LongNumber mod(const LongNumber& _number) const;
	int cmp(const LongNumber& _number) const;
	int cmpFrom(const LongNumber& _number, const lnum_it position) const;
	void printFrom(const lnum_it position)const;
	LongNumber subtract_natural(const LongNumber& _number) const;
	LongNumber& subtract_natural(LongNumber& _number);
	
	LongNumber& Trim();
	LongNumber& TrimFrom(const lnum_it position);

	LongNumber& powerTen(int power);

public:

	LongNumber();
	LongNumber(int number);
	LongNumber(std::string str);
	LongNumber(const LongNumber& longNumber);
	~LongNumber();

	lnum_it begin()const { return m_number.begin(); }
	lnum_it rbegin()const{ return m_number.rbegin(); }
	lnum_it end()const { return m_number.end(); }
	lnum_it rend()const{ return m_number.rend(); }

	int size()const { return m_number.size(); }

	byte& operator[](int index){ return m_number[index]; }
	const byte& operator[](int index) const{ return m_number[index]; }

	bool IsZero()const { return !*begin(); }

	LongNumber& push_back(const byte& number);

	virtual LongNumber& operator++();
	virtual LongNumber& operator--();

	virtual LongNumber& operator=(const LongNumber& _number);

	

	friend LongNumber operator+(const LongNumber& number1, const LongNumber& number2);
	friend LongNumber operator-(const LongNumber& number1, const LongNumber& number2);
	friend LongNumber operator*(const LongNumber& number1, const LongNumber& number2);
	friend LongNumber operator/(const LongNumber& number1, const LongNumber& number2);
	friend LongNumber operator%(const LongNumber& number1, const LongNumber& number2);

	friend bool operator==(const LongNumber& number1, const LongNumber& number2);
	friend bool operator!=(const LongNumber& number1, const LongNumber& number2);
	friend bool operator<(const LongNumber& number1, const LongNumber& number2);
	friend bool operator>(const LongNumber& number1, const LongNumber& number2);
	friend bool operator<=(const LongNumber& number1, const LongNumber& number2);
	friend bool operator>=(const LongNumber& number1, const LongNumber& number2);

	int toInt();

	friend std::ostream& operator<<(std::ostream& out, const LongNumber& longNumber);
	friend std::istream& operator>>(std::istream& in, LongNumber& longNumber);
    
	std::string toString();
};





