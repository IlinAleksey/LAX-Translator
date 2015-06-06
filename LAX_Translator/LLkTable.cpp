#include "LLkTable.h"


LLkTable::LLkTable()
{
}

LLkTable::LLkTable(int control_tables_size, int symbol_tables_size)
{

}

LLkTable::~LLkTable()
{
}

const LLkTableAction& LLkTable::get_action(int table_number, Sequence column) const
{
	return control_tables[table_number].find(column)->second;
}