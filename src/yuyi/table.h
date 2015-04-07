#ifndef __my__table
#define __my__table
#define INVALID -0601
#include "../MyString/MyString.h"
#include <vector>

class TypeTable
{
public:
	enum {T_INT, T_CHAR, T_ARRAY, T_RECORD} type;
	
	struct 
	{
		int low;
		int up;
		int elem_type;//在 类型总表 中的 索引
	}array_attr;
	
	struct __record_attr
	{
		typedef struct 
		{
			MyString name;
			int field_type; //在 类型总表 中的 索引
			int offset;
		}Field;
		std::vector<Field> fields;
	}record_attr;

	typedef std::vector<TypeTable> G_Type_Table;
	static G_Type_Table g_type_table; //类型总表

	TypeTable();
	~TypeTable();

	int getSize();
};

class IdTable
{
public:
	MyString name;
	enum {K_TYPE=0, K_VAR, K_PROC, K_END} kind;
	int level;
	int offset;
	int type; //在 类型总表 中的 索引， 说明了 变量的类型 或 类型别名 的 真实类型
	int param_num; //参数个数, 当这是一个过程标示符 时，此值说明了此项之后的 多少项都是参数
	int access;         //0 dir ,1 indir
	typedef std::vector<IdTable> G_Id_Table;
	static G_Id_Table g_id_table; //标示符总表

	int start;

	IdTable();
	~IdTable();
};
#endif