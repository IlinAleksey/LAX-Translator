#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string>
#include "LongNumber.h"
const int hashtableSize = 100;
class Hashtable
{
	struct entry_s {
		std::string key;
		LongNumber* value;
		struct entry_s *next;
	};

	int m_size;
	entry_s **m_table;
	int hashFunc(const std::string& key);
	
public:
	
	Hashtable(int size = hashtableSize);
	~Hashtable();
	LongNumber* insert(const std::string& key, const LongNumber& value);
	LongNumber* getElement(const std::string& key);
};

