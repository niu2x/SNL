#include "table.h"
#include <vector>
#include <assert.h>
#include "../IO/StdinReader.h"
#include "../IO/file.h"
#include "../general/error.h"
#define gTypeTable (TypeTable::g_type_table)       //全局类型表
#define gIdTable (IdTable::g_id_table)				//全局的符号表
#define BOOLTYPE -0601						//布尔类型，用以区别 一个表达式 的结果是布尔值
#define niuxr_magic -0601 //这是个bug,但也将就

std::vector<int> starts;                //为了区分作用域的起始位置
std::vector<MyString> rows;				//语法树的每一行

int offset[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  //用来处理嵌套的作用域
int LEVEL = 0;									//当前层数

void initBaseType();
void readTree();
bool isDepthOn(const MyString &row, int n);

IdTable* existInCurrentLevel(const MyString &name);
IdTable* existInAll(const MyString &name);
IdTable processOneTypeTickName(int depth);
std::vector<IdTable> processOneLineVariable(int depth);
void TypeK(int depth);
void VarK(int depth);
int processExp(int, int * p=0, int *value = 0);
void StmLK(int);
void ProcDecK(int depth);
void processRead(int depth);
int processBaseTypeVariable(int depth);
void processWrite(int depth);
void processCall(int depth);
void processAssign(int depth);
void processWhile(int depth);
void processReturn(int depth);
void outputIdTable();
void outputTypeTable();
void output();

void initBaseType()
{
	TypeTable intType;
	intType.type = TypeTable::T_INT;
	gTypeTable.push_back(intType);
	
	TypeTable charType;
	charType.type = TypeTable::T_CHAR;
	gTypeTable.push_back(charType);
}

void readTree()
{
	MyString text = StdinReader().read ();
//	MyString text = File("../../2.txt").read ();
	rows = text.split("\n");
}

bool isDepthOn(const MyString &row, int n)
{
	return row.start_with(MyString("    ")*n) && row[n*4] != " ";
}

IdTable* existInCurrentLevel(const MyString &name)
{
	if(gIdTable.empty()) return 0;

	int i = gIdTable.size()-1;
	int targetLevel = LEVEL;

	while(i >= 0)
	{
		if(gIdTable[i].kind == IdTable::K_END && gIdTable[i].level <= targetLevel)
		{
			break;
		}
		else if(gIdTable[i].level > targetLevel)
		{
		}
		else if(gIdTable[i].level < targetLevel)
		{
			break;
		}
		else if(gIdTable[i].name == name)
		{
			return &(gIdTable[i]);
		}
		i--;
	}
	return 0;
}

IdTable* existInAll(const MyString &name)
{
	if(gIdTable.empty()) return 0;

	int i = gIdTable.size()-1;
	int targetLevel = LEVEL;

	while(i >= 0)
	{
		IdTable ttt = gIdTable[i];
		MyString nnnn = gIdTable[i].name;
		if(gIdTable[i].level > targetLevel)
		{
		}
		else if(gIdTable[i].level == LEVEL && gIdTable[i].kind == IdTable::K_END)
		{
			targetLevel--;
			continue;
		}
		else if(gIdTable[i].level < targetLevel)
		{
			targetLevel--;
			continue;
		}
		else if(gIdTable[i].name == name)
		{
			return &(gIdTable[i]);
		}
		i--;
	}
	return 0;
}



std::vector<IdTable> processOneLineVariable(int depth)
{
	IdTable t = processOneTypeTickName(depth);
	t.kind = IdTable::K_VAR;

	std::vector<MyString> names = t.name.split(" ");
	
	std::vector<IdTable> ret;

	for(int i = 0; i < names.size(); i ++)
	{
		t.name = names[i];
		t.offset = offset[LEVEL];
		int temp = gTypeTable[t.type].getSize();
		offset[LEVEL] += gTypeTable[t.type].getSize();
		ret.push_back(t);
	}
	return ret;
}

IdTable processOneTypeTickName(int depth)
{
	MyString row = rows[0].lstrip();
	IdTable id_item;
	id_item.kind = IdTable::K_TYPE;
	id_item.level = LEVEL;
	row = row(5, row.get_length ());
	if(row.start_with("Var"))
	{
		row = row(4, row.get_length ());
		id_item.access = 1;
	}
	else
	{
		id_item.access = 0;
	}
	id_item.name = row(row.rfind ("  ")+2, row.get_length ()).rstrip();
	if(row.start_with ("Integer"))
	{
		id_item.type = 0;
		rows.erase(rows.begin());
	}
	else if(row.start_with ("Char"))
	{
		id_item.type = 1;
		rows.erase(rows.begin());
	}
	else if(row.start_with ("ArrayK"))
	{
		row = row(8, row.get_length ());
		int dot_pos = row.find (".");
		MyString lowStr = row(0, dot_pos);

		row = row(dot_pos + 2, row.get_length ());
		int rfkh_pos = row.find("]");
		MyString upStr = row(0, rfkh_pos);

		row = row(rfkh_pos + 5, row.get_length ()); 

		int elemTypeEndPos = row.find("  ");
		MyString elemTypeStr = row(0, elemTypeEndPos);
				
		TypeTable newType;
		newType.type = TypeTable::T_ARRAY;
		newType.array_attr .low = atoi(lowStr.c_str ());
		newType.array_attr .up = atoi(upStr.c_str ());
		if(elemTypeStr == "Integer")
		{
			newType.array_attr .elem_type = 0;
		}
		else if(elemTypeStr == "Char")
		{
			newType.array_attr .elem_type = 1;
		}
		else
		{
			error("数组 的 元素类型 %s 不合适\n", elemTypeStr.c_str ());
		}
		gTypeTable.push_back(newType);

		id_item.type = gTypeTable.size() - 1;
		rows.erase(rows.begin());
	}
	else if(row.start_with ("RecordK"))
	{
		rows.erase(rows.begin());
		TypeTable newType;
		newType.type = TypeTable::T_RECORD;
		LEVEL ++;
		offset[LEVEL] = 0;
		while((!rows.empty()) && isDepthOn(rows[0], depth + 1))
		{
			std::vector<IdTable> id_items = processOneLineVariable(depth + 1);
			for(std::vector<IdTable>::iterator it = id_items.begin(); it != id_items.end(); it ++)
			{
				TypeTable::__record_attr::Field field;
				field.name = (*it).name;
				field.offset = (*it).offset;;
				field.field_type = (*it).type;
				newType.record_attr .fields .push_back(field);
			}
		}
		LEVEL --;
		gTypeTable.push_back(newType);
		id_item.type = gTypeTable.size() - 1; 
	}
	else
	{
		MyString typeName = row.split(" ")[0];
		IdTable *ret = existInAll(typeName);
		if(ret && ret->kind == IdTable::K_TYPE)
		{	
			id_item.type = ret->type;
			rows.erase(rows.begin());
		}
		else
			error("%s 不是类型标示符\n", typeName.c_str ());
	}
	return id_item;
}

void TypeK(int depth)
{
	rows.erase(rows.begin());
	while(!rows.empty())
	{
		if(isDepthOn(rows[0], depth + 1))
		{
			IdTable id_item = processOneTypeTickName(depth + 1);
			if(existInCurrentLevel(id_item.name) == 0)
			{
				gIdTable.push_back(id_item);
			}
			else
			{
				error("重复的声明 %s.\n", id_item.name.c_str ());
			}
		}
		else
		{
			break;
		}
	}
}

void VarK(int depth)
{
	rows.erase(rows.begin());
	while((!rows.empty()) && isDepthOn(rows[0], depth + 1))
	{
		MyString temp = rows[0];
		std::vector<IdTable> id_items = processOneLineVariable(depth + 1);
		for(std::vector<IdTable>::iterator it = id_items.begin(); it != id_items.end(); it ++)
		{
			IdTable temptemp = *it;
			if(existInCurrentLevel((*it).name) == 0)
			{
				gIdTable.push_back((*it));
			}
			else
			{
				error("重复的声明 %s .", (*it).name.c_str());
			}
		}
	}
}

void ProcDecK(int depth)
{
	MyString row = rows[0];
	rows.erase(rows.begin());

	MyString name = row.split (" ")[1];
	IdTable proc;
	proc.name = name;
	proc.kind = IdTable::K_PROC;
	proc.level = LEVEL;
	

	int i = 0;
	MyString ttemp = rows[i].lstrip();
	while(rows[i].lstrip().start_with("DecK"))
	{
		i ++;
	}

	proc.param_num = i;
	gIdTable.push_back(proc);
	LEVEL ++;
	offset[LEVEL] = 0;
	while(rows[0].lstrip().start_with("DecK"))
	{
		std::vector<IdTable> id_items = processOneLineVariable(depth + 1);
		for(std::vector<IdTable>::iterator it = id_items.begin(); it != id_items.end(); it ++)
		{
			if(existInCurrentLevel((*it).name) == 0)
			{
				gIdTable.push_back((*it));
			}
			else
			{
				error("重复的声明 %s.", (*it).name.c_str());
			}
		}
	}

	while(isDepthOn(rows[0], depth + 1))
	{
		MyString temp = rows[0];

		if(rows[0].lstrip().start_with("TypeK"))
		{
			TypeK(depth + 1);
		}
		else if(rows[0].lstrip().start_with ("VarK"))
		{
			VarK(depth + 1);
		}
		else if(rows[0].lstrip().start_with ("ProcDecK"))
		{
			starts.push_back(gIdTable.size());	
			ProcDecK(depth + 1);
			int start = starts[starts.size()-1];
			starts.pop_back();
			IdTable end;
			end.kind = IdTable::K_END;
			end.level = LEVEL+1;
			end.start = start;
			gIdTable.push_back(end);
		}
		else if(rows[0].lstrip().start_with ("StmLK"))
		{
			StmLK(depth + 1);
		}
		else
		{
			error("这像是个语法错误, 正常不应出现\n.");
		}
	}
	-- LEVEL;
}
void processRead(int depth)
{
	MyString row = rows[0];
	rows.erase(rows.begin());
	MyString name = row.split (" ")[2];
	IdTable *var = existInAll(name);
	if(var && var->kind == IdTable::K_VAR && (var->type == 0 || var->type == 1))
	{
	}
	else
	{
		error("read 语句中 的 %s 不合适.", name.c_str ());
	}
}

int processBaseTypeVariable(int depth)
{
	MyString row = rows[0];
	rows.erase(rows.begin());
	row = row.lstrip();

	if(row.start_with("ExpK Const")) 
		return 0;
	else if(row.start_with("ExpK IdV"))
	{
		MyString idName = row.split(" ")[2];
		IdTable *var = existInAll(idName);
		if(var && var->kind == IdTable::K_VAR)
		{
			return var->type;
		}
		else
			error("出人意料的变量标示符 %s .", idName.c_str ());
	}
	else if(row.start_with("ExpK ArrayMembV"))
	{
		MyString idName = row.split(" ")[2];
		IdTable *var = existInAll(idName);
		if(var && var->kind == IdTable::K_VAR && gTypeTable[var->type].type == TypeTable::T_ARRAY)
		{
			int access;
			int index;
			if(processExp(depth + 1, &access, &index) == 0)
			{
				if(index==niuxr_magic||(index >= gTypeTable[var->type].array_attr.low && index <= gTypeTable[var->type].array_attr.up))
					return gTypeTable[var->type].array_attr.elem_type;
				else
					error("%s[%d] 越界了.", idName.c_str (), index);
			}
			else
				error("你应用 一个 整数表达式 来 索引 数组 %s.\n", idName.c_str ());
		}
		else
			error("%s 压根儿就不是个数组", idName.c_str ());
	}
	else if(row.start_with("ExpK FieldMembV"))
	{
		MyString idName = row.split(" ")[2];
		IdTable *var = existInAll(idName);
		if(var && var->kind == IdTable::K_VAR && gTypeTable[var->type].type == TypeTable::T_RECORD)
		{
			row = rows[0];
			rows.erase(rows.begin());
			row = row.lstrip();
			if(row.start_with ("ExpK IdV"))
			{
				MyString memIdName = row.split(" ")[2];
				std::vector<TypeTable::__record_attr::Field> fields = gTypeTable[var->type].record_attr.fields;
				for(std::vector<TypeTable::__record_attr::Field>::iterator it = fields.begin(); it != fields.end(); it++)
				{
					if((*it).name == memIdName)
						break;
				}
				if(it != fields.end())
				{
					return (*it).field_type;
				}
				else
				{
					error("记录%s 没有 %s 域.", idName.c_str (), memIdName.c_str ());
				}
			}
			else if(row.start_with ("ExpK ArrayMembV"))
			{
				MyString memIdName = row.split(" ")[2];
				std::vector<TypeTable::__record_attr::Field> fields = gTypeTable[var->type].record_attr.fields;
				for(std::vector<TypeTable::__record_attr::Field>::iterator it = fields.begin(); it != fields.end(); it++)
				{
					if((*it).name == memIdName)
						break;
				}
				if(it != fields.end())
				{
					if(gTypeTable[(*it).field_type].type == TypeTable::T_ARRAY)
					{
						int access, index;
						if(processExp(depth + 2, &access, &index) == 0)
						{
							if(index==niuxr_magic||(index >= gTypeTable[(*it).field_type].array_attr.low && index <= gTypeTable[(*it).field_type].array_attr.up))
								return gTypeTable[(*it).field_type].array_attr.elem_type;
							else
								error("%s[%d] 越界了.", memIdName.c_str (), index);
						}
						else
							error("你应用 一个 整数表达式 来 索引 数组 %s.\n", memIdName.c_str ());
					}
					else
					{
						error("%s 压根儿就不是个数组", memIdName.c_str ());
					}
				}
				else
				{
					error("记录%s 没有 %s 域.", idName.c_str (), memIdName.c_str ());
				}
			}
			else
			{
				error("这个错误不该遇到，如果遇到，表明[语法分析]程序内部有错误.");
			}
		}
		else
			error("%s 压根儿就不是个数组", idName.c_str ());
	}
	else
		error("意料之外的行 %s.", row.c_str ());
}

int processExp(int depth, int *access, int *value)   //access 1 表示可以当形参用
{
	if(access) *access = 0;
	MyString row = rows[0];
	row = row.lstrip();

	if(value)
	{
		if(row.start_with("ExpK Const"))
		{
			*value = atoi(row.split(" ")[2].c_str());
		}
		else
		{
			*value = niuxr_magic;
		}
	}

	if(row.start_with("ExpK FieldMembV") || row.start_with("ExpK ArrayMembV") || row.start_with("ExpK Const") || row.start_with("ExpK IdV"))
	{
		if(access)
		{
			if(row.start_with("ExpK FieldMembV") || row.start_with("ExpK ArrayMembV") || row.start_with("ExpK IdV"))
			{
				*access = 1;
			}
		}
		return processBaseTypeVariable(depth);
	}
	else if(row.start_with ("ExpK Op"))
	{
		rows.erase(rows.begin());
		if(processExp(depth+1) == 0 && processExp(depth+1) == 0)
		{
			if(row.split(" ")[2] == "<" || row.split(" ")[2] == "=")
			{
				return BOOLTYPE;//代表布尔类型
			}
			else
			{
				return 0;
			}
		}
		else
			error("运算符 两侧 类型不一致\n");
	}
	else
		error("意料之外的表达式结构.");
}
void processWrite(int depth)
{
	rows.erase(rows.begin());

	int ret = processExp(depth + 1);

	if(ret != 0 && ret!= 1)
		error("只能write一个整数或字符.");
}

void processCall(int depth)
{
	rows.erase(rows.begin());
	MyString funcname = rows[0];  
	rows.erase(rows.begin());

	if(!(funcname.lstrip ().start_with("ExpK IdV")))
	{
		error("不知道 函数调用 调用谁.但这错误也不该有,如果有,是语法分析错了.\n");
	}

	funcname = funcname.split(" ")[2];

	IdTable *proc = existInAll(funcname);

	if((!proc) || (proc->kind != IdTable::K_PROC))
	{
		error("%s 不是个过程名.", funcname.c_str ());
	}

	for(int i = 0; i < gIdTable.size(); i ++)
	{
		if(&(gIdTable[i]) == proc)
			break;
	}
	assert(i < gIdTable.size());

	int count = 0;
	while(!(rows.empty()) && isDepthOn(rows[0], depth+1))
	{
		int access;
		int paramType = processExp(depth + 1, &access);
		if(proc->param_num >= count + 1)
		{
			IdTable temp = gIdTable[i + count];
			if(gIdTable[i +1+ count].type !=  paramType)
			{
				error("Call %s 参数类型不匹配.", funcname.c_str ());
			}
			if(gIdTable[i +1+ count].access == 1 && access == 0)
			{
				error("Call %s 变参值参不匹配.", funcname.c_str ());
			}
		}
		else
		{
			error("Call %s 参数 个数不一致.", funcname.c_str ());
		}
		count ++;
	}

	if(count != proc->param_num)
		error("Call %s 参数 个数不一致.", funcname.c_str ());
}

void processAssign(int depth)
{
	rows.erase(rows.begin());
	if(processBaseTypeVariable(depth + 1) == processExp(depth + 1))
	{
	}
	else
	{
		error("赋值号 两侧 类型不一致.");
	}
}

void processIf(int depth)
{
	rows.erase(rows.begin());
	if(processExp(depth + 1) != BOOLTYPE) error();
	StmLK(depth + 1);
	if(!(rows.empty()) && isDepthOn(rows[0], depth+1))
	{
		StmLK(depth + 1);
	}
}




void processWhile(int depth)
{
	rows.erase(rows.begin());
	if(processExp(depth + 1) != BOOLTYPE) error();
	StmLK(depth + 1);
}

void processReturn(int depth)
{
	rows.erase(rows.begin());
}
void StmLK(int depth)
{
	rows.erase(rows.begin());

	while((!rows.empty()) && isDepthOn(rows[0], depth + 1))
	{
		if(rows[0].lstrip().start_with("StmtK assign"))
		{
			processAssign(depth + 1);
		}
		else if(rows[0].lstrip().start_with ("StmtK read"))
		{
			processRead(depth + 1);
		}
		else if(rows[0].lstrip().start_with ("StmtK while"))
		{
			processWhile(depth + 1);
		}
		else if(rows[0].lstrip().start_with ("StmtK if"))
		{
			processIf(depth + 1);
		}
		else if(rows[0].lstrip().start_with ("StmtK write"))
		{
			processWrite(depth + 1);
		}
		else if(rows[0].lstrip().start_with ("StmtK call"))
		{
			processCall(depth + 1);
		}
		else if(rows[0].lstrip().start_with ("StmtK return"))
		{
			processReturn(depth + 1);
		}
		else
		{
			error("意外的语句类型, 不该有此错.");
		}
	}
}
void outputIdTable()
{
	printf("标示符表\n");
	printf("│序号\t");
	printf("│名字\t\t");
	printf("│KIND\t");
	printf("│层数\t");
	printf("│访问\t");
	printf("│偏移\t");
	printf("│类型\t");
	printf("│参数\t");
	printf("│头标\n");
/*	printf("│INDEX\t");
	printf("│NAME\t\t");
	printf("│KIND\t");
	printf("│LEVEL\t");
	printf("│ACCESS\t");
	printf("│OFFSET\t");
	printf("│TYPE\t");
	printf("│PARAM\t");
	printf("│START\n");*/
	printf("├───┼───────┼───┼───┼───┼───┼───┼───┼───┤\n");
	for(int i = 0; i < gIdTable.size(); i++)
	{
		printf("│%2d\t", i);
		printf("│%10s\t", gIdTable[i].name.c_str());
		char *s[] = {"TYPE", "VAR", "PROC", "END"};
		printf("│%4s\t", s[gIdTable[i].kind]);
		if(gIdTable[i].level != INVALID)
			printf("│%d\t", gIdTable[i].level);
		else
			printf("│ \t");
		if(gIdTable[i].access != INVALID)
			printf("│%d\t", gIdTable[i].access);
		else
			printf("│ \t");
		if(gIdTable[i].offset != INVALID)
			printf("│%3d\t", gIdTable[i].offset);
		else
			printf("│   \t");
		if(gIdTable[i].type != INVALID)
			printf("│%d\t", gIdTable[i].type);
		else
			printf("│ \t");
		if(gIdTable[i].param_num != INVALID)
			printf("│%d\t", gIdTable[i].param_num);
		else
			printf("│ \t");
		if(gIdTable[i].start != INVALID)
			printf("│%2d\t", gIdTable[i].start);
		else
			printf("│  \t");
		printf("│\n");
		printf("├───┼───────┼───┼───┼───┼───┼───┼───┼───┤\n");
	}
}
void outputTypeTable()
{
	printf("类型表\n");
	printf("│序号\t");
	printf("│类型\t");
	printf("│下界\t");
	printf("│上界\t");
	printf("│元素类型\t");
	printf("│域(名字, 类型, 偏移)\n");
	printf("├───┼───┼───┼───┼───────┼───────────────┤\n");
	for(int i = 0; i < gTypeTable.size(); i++)
	{
		if(gTypeTable[i].type == TypeTable::T_INT)
		{
			printf("│%2d\t│INT\t│\t│\t│\t\t│          \t   \t   \t│\n", i);
		}
		else if(gTypeTable[i].type == TypeTable::T_CHAR)
		{
			printf("│%2d\t│CHAR\t│\t│\t│\t\t│          \t   \t   \t│\n", i);
		}
		else if(gTypeTable[i].type == TypeTable::T_ARRAY)
		{
			printf("│%2d\t│ARRAY\t│%4d\t│%4d\t│%2d\t\t│          \t   \t   \t│\n", i, gTypeTable[i].array_attr.low, gTypeTable[i].array_attr.up, gTypeTable[i].array_attr.elem_type);
		}
		else if(gTypeTable[i].type == TypeTable::T_RECORD)
		{
			printf("│%2d\t│REC\t│\t│\t│\t\t│          \t   \t   \t│\n", i);
			for(int k = 0; k < gTypeTable[i].record_attr.fields.size(); k ++)
			{	
				printf("│  \t│   \t│\t│\t│\t\t│%-10s\t%3d\t%3d\t│\n", gTypeTable[i].record_attr.fields[k].name.c_str(), gTypeTable[i].record_attr.fields[k].field_type, gTypeTable[i].record_attr.fields[k].offset);
			}
		}
		printf("├───┼───┼───┼───┼───────┼───────────────┤\n");
	}
}

void output()
{
	printf("\n\n");
	outputTypeTable();
	printf("\n\n");
	outputIdTable();
}

int main()
{
	atexit(output);
	readTree();
	initBaseType();

	if(rows.empty()) exit(1);

	rows.erase(rows.begin());

	starts.push_back(gIdTable.size());

	while(!rows.empty())
	{
		MyString row = rows[0];
		if(isDepthOn(row, 1))
		{
			if(row.lstrip().start_with("TypeK"))
			{
				TypeK(1);
			}
			else if(row.lstrip().start_with ("VarK"))
			{
				VarK(1);
			}
			else if(row.lstrip().start_with ("ProcDecK"))
			{
				
				starts.push_back(gIdTable.size());
				
				ProcDecK(1);

				int start = starts[starts.size()-1];
				starts.pop_back();

				IdTable end;
				end.kind = IdTable::K_END;
				end.level = LEVEL + 1;
				end.start = start;
				gIdTable.push_back(end);
			}
			else if(row.lstrip().start_with ("StmLK"))
			{
				StmLK(1);
			}
			else
			{
				rows.erase(rows.begin());
			}
		}
		else
		{
			error();
		}
	}
	output();
	return 0;
}