#include "table.h"

TypeTable::TypeTable()
{
	
}
TypeTable::~TypeTable ()
{
}
TypeTable::G_Type_Table TypeTable:: g_type_table;

int TypeTable::getSize ()
{
	switch(type)
	{
		case T_INT:
			return 4;
			break;
		case T_CHAR:
			return 1;
			break;
		case T_ARRAY:
			return (array_attr.up - array_attr.low + 1) * g_type_table[array_attr.elem_type].getSize();
			break;
		case T_RECORD:
			{
				int sum = 0;
				for(int i = 0; i < record_attr.fields.size(); i ++)
				{
					sum += g_type_table[record_attr.fields[i].field_type].getSize();
				}
				return sum;
			}
			break;
	}
	return 0;
}

IdTable::IdTable()
{
	offset = INVALID;
	param_num = INVALID;
	type = INVALID;
	start = INVALID;
	access = INVALID;
}
IdTable::~IdTable ()
{
}
IdTable::G_Id_Table IdTable:: g_id_table;