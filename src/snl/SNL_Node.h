#ifndef __my_snl_node
#define __my_snl_node

#include <vector>
#include "../MyString/MyString.h"

class SNL_Node
{
public:
	enum KINDDEC {ArrayK = 0, CharK, IntegerK, RecordK, IdK};
	enum KINDSTMT {IfK = 0, WhileK, AssignK, ReadK, WriteK, CallK, ReturnK};
	enum KINDEXP {OpK = 0, ConstK, IdKK} ;
	enum PARAMT {valparamtype = 0, varparamtype = 1} ;
	enum OPOP {LT=0, EQ, PLUS, MINUS, TIMES, OVER, LKH, RKH, S_END};
	enum VARKIND {IdV = 0, ArrayMembV, FieldMembV};

	SNL_Node *child[3];
	SNL_Node *sibling;
	int lineno;
	enum {Prok = 0, PheadK, TypeK, VarK, ProcDecK, StmLK, DecK, StmtK, Expk}nodekind;
	union 
	{
		enum KINDDEC dec;
		enum KINDSTMT stmt;
		enum KINDEXP exp;
	}kind;
	//int idnum;
	std::vector<MyString> name;
	//table
	struct __name
	{
		struct 
		{
			int low;
			int up;
			enum KINDDEC childType;
		}arrayAttr;
		struct __procAttr
		{
			enum PARAMT paramt;
			__procAttr()
			{
				paramt = valparamtype;
			}
		}procAttr;
		struct
		{
			enum OPOP op;
			int val;
			enum VARKIND varkind;
			enum {Void = 0, Integer, Boolean}type;
		}expAttr;
	}attr;

	std::vector<MyString> type_name;
	SNL_Node();
	~SNL_Node();
};

#endif