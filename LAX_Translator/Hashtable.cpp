#include "Hashtable.h"




Hashtable::Hashtable(int size)
{
	
	m_table = new entry_s*[size];

	
	for (int i = 0; i < size; i++) {
		m_table[i] = NULL;
	}

	m_size = size;

}

Hashtable::~Hashtable()
{
	for (int i = 0; i < m_size; i++) {
		delete m_table[i];
	}
}

int Hashtable::hashFunc(const std::string& key)
{
	unsigned long int hashval=0;
	int i = 0;

	/* Convert our string to an integer */
	while (hashval < ULONG_MAX && i < key.size()) {
		hashval = hashval << 8;
		hashval += key[i];
		i++;
	}

	return hashval % m_size;
}
LongNumber* Hashtable::insert(const std::string& key, const LongNumber& value)
{
	int bin = 0;
	
	entry_s *next = NULL;
	entry_s *last = NULL;

	bin = hashFunc(key);

	next = m_table[bin];

	while (next != NULL  && key>next->key) {
		last = next;
		next = next->next;
	}

	if (next != NULL  && key == next->key) {

		return (next->value);

	}
	else {
		entry_s* newpair = new entry_s;
		newpair->key = key;
		newpair->value = new LongNumber;
		*(newpair->value)=	value;
		newpair->next = NULL;

		/* We're at the start of the linked list in this bin. */
		if (next == m_table[bin]) {
			newpair->next = next;
			m_table[bin] = newpair;

			/* We're at the end of the linked list in this bin. */
		}
		else if (next == NULL) {
			last->next = newpair;

			/* We're in the middle of the list. */
		}
		else  {
			newpair->next = next;
			last->next = newpair;
		}
		return (newpair->value);
	}
	
}
LongNumber* Hashtable::getElement(const std::string& key)
{
	return NULL;
}