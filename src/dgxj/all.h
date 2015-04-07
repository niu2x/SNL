#include "../snl/SNL_Node.h"

SNL_Node *Program(void);				//总程序处理分析程序
SNL_Node * ProgramHead(void);			//程序头部分处理分析程序
SNL_Node * DeclarePart(void);			//程序声明部分处理分析程序
SNL_Node * TypeDec(void);				//类型声明处理分析程序
SNL_Node * TypeDeclaration(void);		//类型声明中的其它函数
SNL_Node * TypeDecList(void);			//类型声明中的其它函数
SNL_Node * TypeDecMore(void);			//类型声明中的其他函数
void TypeId(SNL_Node * t);				//类型声明中类型标识符处理分析程序
void TypeDef(SNL_Node * t);				//具体类型处理分析程序
void BaseType(SNL_Node * t);			//基本类型处理分析程序
void StructureType(SNL_Node * t);		//结构类型处理分析程序
void ArrayType(SNL_Node * t);			//数组类型处理分析程序
void RecType(SNL_Node * t);				//记录类型处理分析程序
SNL_Node * FieldDecList(void);			//记录类型中的域声明处理分析函数
SNL_Node * FieldDecMore(void);			//记录类型中的其他域声明处理分析函数
void IdList(SNL_Node * t);				//记录类型中标识符名处理分析程序
void IdMore(SNL_Node * t);				//记录类型域中其他标识符名处理分析程序
SNL_Node * VarDec(void);				//变量声明处理分析程序
SNL_Node * VarDeclaration(void);		//变量声明处分处理分析程序
SNL_Node * VarDecList(void);			//变量声明部分处理分析程序
SNL_Node * VarDecMore(void);			//变量声明部分处理分析程序
void VarIdList(SNL_Node * t);			//变量声明部分变量名部分处理分析程序
void VarIdMore(SNL_Node * t);			//变量声明部分变量名部分处理分析程序
SNL_Node * ProcDec(void);				//过程声明部分总的处理分析程序
SNL_Node * ProcDeclaration(void);		//过程声明部分具体的处理分析程序
void ParamList(SNL_Node * t);			//过程声明中的参数声明部分的处理分析程序
SNL_Node * ParamDecList(void);			//过程声明中声明部分的分析处理程序
SNL_Node * ParamMore(void);				//过程声明中参数声明其他部分的处理分析程序
SNL_Node * Param(void);					//过程声明中参数声明中参数部分的分析处理程序
void FormList(SNL_Node * t);			//过程声明中的参数声明中参数名部分的处理分析程序
void FidMore(SNL_Node * t);				//过程声明中的参数声明中参数名部分的处理分析程序
SNL_Node * ProcDecPart(void);			//过程声明部分的处理分析程序
SNL_Node * ProcBody(void);				//过程体部分处理分析程序
SNL_Node * ProgramBody(void);			//主程序题部分处理分析程序
SNL_Node * StmList(void);				//语句序列部分处理分析程序
SNL_Node * StmMore(void);				//更多语句部分处理分析程序
SNL_Node * Stm(void);					//语句递归处理分析程序
SNL_Node * AssCall(void);				//赋值语句和过程调用语句部分的处理分析程序
SNL_Node * AssignmentRest(void);		//赋值语句处理分析函数
SNL_Node * ConditionalStm(void);		//条件语句处理分析程序
SNL_Node * LoopStm(void);				//循环语句处理分析程序
SNL_Node * InputStm(void);				//输入语句处理分析程序
SNL_Node * OutputStm(void);				//输出语句处理分析程序
SNL_Node * ReturnStm(void);				//过程返回语句处理分析程序
SNL_Node * CallStmRest(void);			//过程调用语句处理分析程序
SNL_Node * ActParamList(void);			//实参部分处理分析程序
SNL_Node * ActParamMore(void);			//更多实参部分处理分析程序
SNL_Node * Exp(void);					//表达式递归处理分析程序
SNL_Node * Simple_exp(void);			//简单表达式递归处理分析程序
SNL_Node * Term(void);					//项递归处理分析程序
SNL_Node * Factor(void);				//因子递归处理分析程序
SNL_Node * Variable(void);				//变量处理程序
void VariMore(SNL_Node * t);			//变量其余部分处理程序
SNL_Node * Fieldvar(void);				//域变量处理分析程序
void FieldvarMore(SNL_Node * t);		//域变量其他部分处理分析程序
SNL_Node *ProcMore();
SNL_Node *RelExp();

