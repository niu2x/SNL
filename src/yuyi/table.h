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
		int elem_type;//�� �����ܱ� �е� ����
	}array_attr;
	
	struct __record_attr
	{
		typedef struct 
		{
			MyString name;
			int field_type; //�� �����ܱ� �е� ����
			int offset;
		}Field;
		std::vector<Field> fields;
	}record_attr;

	typedef std::vector<TypeTable> G_Type_Table;
	static G_Type_Table g_type_table; //�����ܱ�

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
	int type; //�� �����ܱ� �е� ������ ˵���� ���������� �� ���ͱ��� �� ��ʵ����
	int param_num; //��������, ������һ�����̱�ʾ�� ʱ����ֵ˵���˴���֮��� ������ǲ���
	int access;         //0 dir ,1 indir
	typedef std::vector<IdTable> G_Id_Table;
	static G_Id_Table g_id_table; //��ʾ���ܱ�

	int start;

	IdTable();
	~IdTable();
};
#endif