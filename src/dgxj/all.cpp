#include "../snl/snl_node.h"
#include "../snl/Token.h"
#include <vector>
#include "../MyString/MyString.h"
#include "all.h"
#include "../general/error.h"
#define NEXTTOKEN tokenList[0].type == Token::T_ID ? tokenList[0].value.charValue.c_str():tokenList[0].type.c_str()
static int lineno = 1;
extern std::vector<Token> tokenList;

Token Match(TokenType);
bool NextIs(TokenType);


SNL_Node *Program()
{
	SNL_Node *t = ProgramHead();
	SNL_Node *q = DeclarePart();
	SNL_Node *s = ProgramBody();

	SNL_Node *root = new SNL_Node();
	root ->nodekind = SNL_Node::Prok;

	if(t) root->child[0] = t;
	else
	{
		error("line[%d] 告诉我程序头在哪里.", lineno);
	}

	if(q) root->child[1] = q;

	if(s) root->child[2] = s;
	else
	{
		error("line[%d] 告诉我程序的躯体在哪里.", lineno);
	}

	Match(Token::T_DOT);

	if(tokenList.size()>0)
		error("程序末尾有一些不该出现的东西");

	return root;
}

SNL_Node *ProgramHead()
{
	SNL_Node *ph = new SNL_Node();
	ph->nodekind = SNL_Node::PheadK;
	Match(Token::T_PROGRAM );
	Token id = Match(Token::T_ID);
	ph->name.push_back(id.value.charValue);
	return ph;
}

SNL_Node *DeclarePart()
{
	SNL_Node *pp = 0;
	SNL_Node *typeP = new SNL_Node();
	typeP->nodekind = SNL_Node::TypeK;
	typeP->child[0] = TypeDec();

	SNL_Node *varP = new SNL_Node();
	varP->nodekind = SNL_Node::VarK;
	varP->child[0] = VarDec();

	SNL_Node *s = ProcDec();

	pp = typeP;

	if(varP->child[0] == 0)
	{
		delete varP;
		varP = s;
	}
	if(typeP->child[0] == 0)
	{
		delete typeP;
		pp = typeP = varP;
	}
	if(typeP != varP)
	{
		typeP->sibling = varP;
	}
	if(varP != s)
	{
		varP->sibling = s;
	}

	return pp;
}

SNL_Node* TypeDec()
{
	SNL_Node *t = 0;
	if(NextIs(Token::T_TYPE))
	{
		t = TypeDeclaration();
	}
	else if(NextIs(Token::T_VAR))
	{
	}
	else if(NextIs(Token::T_PROCEDURE ))
	{
	}
	else if(NextIs(Token::T_BEGIN))
	{
	}
	else
	{
		error("line[%d] 我在等type var procedure begin, 不是等你.", lineno);
	}
	return t;
}

SNL_Node *TypeDeclaration()
{
	Match(Token::T_TYPE );
	SNL_Node *t = TypeDecList();
	if(t == 0)
	{
		error("line[%d] 类型声明不太对.", lineno);
	}
	return t;
}

SNL_Node *TypeDecList()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::DecK;

	TypeId(t);
	Match(Token::T_EQ);
	TypeDef(t);
	Match(Token::T_SEMICOLON );
	SNL_Node *p = TypeDecMore();
	if(p) 
	{
		t->sibling = p;
	}
	return t;
}

SNL_Node *TypeDecMore()
{
	SNL_Node *t = 0;
	if(NextIs(Token::T_VAR )) return t;
	if(NextIs(Token::T_PROCEDURE )) return t;
	if(NextIs(Token::T_BEGIN )) return t;
	if(NextIs(Token::T_ID ))
	{
		t = TypeDecList();
		return t;
	}
	else
	{
		error("line[%d] 你是个合法的类型定义吗.", lineno);
	}
}

void TypeId(SNL_Node *t)
{
	Token id = Match(Token::T_ID );
	t->name.push_back(id.value.charValue );
}

void TypeDef(SNL_Node *t)
{
	if(NextIs(Token::T_INTEGER))
	{
		BaseType(t);
	}
	else if(NextIs(Token::T_CHAR ))
	{
		BaseType(t);
	}
	else if(NextIs(Token::T_ARRAY ))
	{
		StructureType(t);
	}
	else if(NextIs(Token::T_RECORD ))
	{
		StructureType(t);
	}
	else if(NextIs(Token::T_ID))
	{
		t->kind.dec = SNL_Node::IdK;
		Token id = Match(Token::T_ID);
		t->type_name.push_back(id.value.charValue);
	}
	else
	{
		error("line[%d] 你是个我认识的类型标示符?.", lineno);
	}
}

void BaseType(SNL_Node *t)
{
	if(NextIs(Token::T_INTEGER))
	{
		Match(Token::T_INTEGER);
		t->kind.dec = SNL_Node::IntegerK;
	}
	else if(NextIs(Token::T_CHAR ))
	{
		Match(Token::T_CHAR);
		t->kind.dec = SNL_Node::CharK;
	}
	else
	{
		error("line[%d] 我只喜欢整数和字符.", lineno);
	}
}

void StructureType(SNL_Node *t)
{
	if(NextIs(Token::T_ARRAY))
	{
		t->kind.dec = SNL_Node::ArrayK;
		ArrayType(t);
	}
	else if(NextIs(Token::T_RECORD ))
	{
		t->kind.dec = SNL_Node::RecordK;
		RecType(t);
	}
	else
	{
		error("line[%d] 我只期待Record和Array.", lineno);
	}
}	

void ArrayType(SNL_Node *t)
{
	Match(Token::T_ARRAY);
	Match(Token::T_L_FKH);
	Token iv = Match(Token::T_INTEGER_VALUE);
	t->attr.arrayAttr.low = iv.value .intValue;
	Match(Token::T_RANGE);
	iv = Match(Token::T_INTEGER_VALUE);
	t->attr.arrayAttr.up = iv.value .intValue;
	Match(Token::T_R_FKH);
	Match(Token::T_OF);
	BaseType(t);
	t->attr.arrayAttr .childType = t->kind.dec;
	t->kind.dec = SNL_Node::ArrayK;
}	

void RecType(SNL_Node *t)
{
	Match(Token::T_RECORD );

	SNL_Node * p = FieldDecList();

	if( p == 0)
	{
		error("line[%d] 记录的定义不怎么对.", lineno);
	}

	t->child[0] = p;

	Match(Token::T_END );
}

SNL_Node* FieldDecList()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::DecK;
	SNL_Node *p = 0;

	if(NextIs(Token::T_INTEGER) || NextIs(Token::T_CHAR))
	{
		BaseType(t);
		IdList(t);
		Match(Token::T_SEMICOLON);
		p = FieldDecMore();
	}
	else if(NextIs(Token::T_ARRAY))
	{
		ArrayType(t);
		IdList(t);
		Match(Token::T_SEMICOLON);
		p = FieldDecMore();
	}
	else
	{
		error("line[%d] 记录里只能出现 整数 字符 和 数组.", lineno);
	}
	t->sibling = p;
	return t;
}

SNL_Node* FieldDecMore()
{
	SNL_Node *t = 0;
	Token aaa = tokenList[0];
	if(NextIs(Token::T_END))
	{
		return t;
	}

	if(NextIs(Token::T_INTEGER) || NextIs(Token::T_CHAR) || NextIs(Token::T_ARRAY))
	{
		return FieldDecList();
	}
	
	error("line[%d] 记录的定义又不对了.", lineno);

}

void IdList(SNL_Node *t)
{
	Token id = Match(Token::T_ID);
	t->name.push_back(id.value .charValue );
	IdMore(t);
}

void IdMore(SNL_Node *t)
{
	if(NextIs(Token::T_SEMICOLON)) return;
	
	Match(Token::T_COMMA);

	IdList(t);
}

SNL_Node *VarDec()
{
	SNL_Node *t = 0;
	
	if(NextIs(Token::T_PROCEDURE)) return t;
	if(NextIs(Token::T_BEGIN)) return t;
	if(NextIs(Token::T_VAR))
		return VarDeclaration();
	error("line[%d] 我在期待过程定义 程序体 或 变量声明.", lineno);
}

SNL_Node *VarDeclaration()
{
	Match(Token::T_VAR);
	SNL_Node *t = VarDecList();
	if(t == 0)
	{
		error("line[%d] 错误的变量声明.", lineno);
	}
	return t;
}

SNL_Node *VarDecList()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::DecK;

	SNL_Node *p=0;
	TypeDef(t);
	VarIdList(t);
	Match(Token::T_SEMICOLON);
	p = VarDecMore();
	t->sibling = p;
	return t;
}

SNL_Node *VarDecMore()
{
	SNL_Node *t = 0;

	if(NextIs(Token::T_PROCEDURE))  return t;
	if(NextIs(Token::T_BEGIN))  return t;

	if(NextIs(Token::T_ARRAY) || NextIs(Token::T_INTEGER) || NextIs(Token::T_CHAR) || NextIs(Token::T_RECORD) || NextIs(Token::T_ID))
	{
		t = VarDecList();
		return t;
	}

	error("line[%d] 此处有错误，该出现的是过程 程序体 或者 更多变量声明.", lineno);
}

void VarIdList(SNL_Node *t)
{
	Token id = Match(Token::T_ID);
	t->name.push_back(id.value .charValue );
	VarIdMore(t);
}

void VarIdMore(SNL_Node *t)
{
	if(NextIs(Token::T_SEMICOLON ))  return;
	Match(Token::T_COMMA);
	VarIdList(t);
}

SNL_Node *ProcDec()
{
	SNL_Node *t = 0;
	if(NextIs(Token::T_BEGIN))
	{
		return t;
	}
	
	if(NextIs(Token::T_PROCEDURE))
	{
		return ProcDeclaration();
	}
	else
	{
		error("line[%d] 你不是我所期待的 过程声明 或 程序体.", lineno);
	}
}

SNL_Node *ProcDeclaration()
{
	SNL_Node * t= new SNL_Node();
	t->nodekind = SNL_Node::ProcDecK;
	Match(Token::T_PROCEDURE );
	
	Token id = Match(Token::T_ID );
	t->name.push_back(id.value .charValue );
	Match(Token::T_L_XKH);
	ParamList(t);
	Match(Token::T_R_XKH);
	Match(Token::T_SEMICOLON);
	t->child[1] = ProcDecPart();
	t->child[2] = ProcBody();
	t->sibling = ProcMore();
	return t;
}

void ParamList(SNL_Node *t)
{
	SNL_Node *p = 0;
	if(NextIs(Token::T_R_XKH))
	{
		return ;
	}
	if(NextIs(Token::T_INTEGER) || NextIs(Token::T_CHAR) || NextIs(Token::T_RECORD) || NextIs(Token::T_ARRAY) || NextIs(Token::T_ID) ||NextIs(Token::T_VAR))
	{
		t->child[0] = ParamDecList();
		return ;
	}
	error("line[%d] 防不胜防的参数声明出错了.", lineno);
}

SNL_Node *ParamDecList()
{
	SNL_Node *t = Param();
	SNL_Node *p = ParamMore();
	t->sibling = p;
	return t;
}

SNL_Node *ParamMore()
{
	SNL_Node *t = 0;
	if(NextIs(Token::T_R_XKH))
	{
		return t;
	}
	else
	{
		if(NextIs(Token::T_SEMICOLON ))
		{
			Match(Token::T_SEMICOLON);
			t = ParamDecList();
			if(t)
			{
				return t;
			}
			else
			{
				error("line[%d] 参数声明不对.", lineno);
			}
		}
		else
		{
			error("line[%d] 不是我翘首以盼的分号.", lineno);
		}
	}
}

SNL_Node* Param()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::DecK;

	if(NextIs(Token::T_INTEGER ) || NextIs(Token::T_CHAR ) || NextIs(Token::T_RECORD ) || NextIs(Token::T_ARRAY ) || NextIs(Token::T_ID ))
	{
		t->attr .procAttr.paramt = SNL_Node::valparamtype;
		TypeDef(t);
		FormList(t);
		return t;
	}
	else
	{
		Match(Token::T_VAR );
		t->attr.procAttr.paramt = SNL_Node::varparamtype;
		TypeDef(t);
		FormList(t);
		return t;
	}
}

void FormList(SNL_Node *t)
{
	Token id = Match(Token::T_ID);
	t->name .push_back(id.value .charValue );
	FidMore(t);
}

void FidMore(SNL_Node *t)
{
	if(NextIs(Token::T_SEMICOLON ) || NextIs(Token::T_R_XKH ))
	{
		return;
	}

	Match(Token::T_COMMA);

	FormList(t);
}

SNL_Node *ProcDecPart()
{
	return DeclarePart();
}

SNL_Node *ProcBody()
{
	SNL_Node *t = ProgramBody();

	if(t == 0) error("line[%d] 程序的躯体何在.", lineno);

	return t;
}

SNL_Node* ProgramBody()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::StmLK;
	Match(Token::T_BEGIN);
	t->child[0] = StmList();
	Match(Token::T_END);
	return t;
}

SNL_Node* StmList()
{
	SNL_Node *t = Stm();
	SNL_Node *p = StmMore();
	t ->sibling = p;
	return t;
}

SNL_Node *StmMore()
{
	SNL_Node *t = 0;

	if(NextIs(Token::T_END ) || NextIs(Token::T_ENDWH) || NextIs(Token::T_FI) || NextIs(Token::T_ELSE)) return t;

	Match(Token::T_SEMICOLON );

	return StmList();
}

MyString temp_name;

SNL_Node * Stm()
{
	if(NextIs(Token::T_IF))
	{
		return ConditionalStm();
	}
	if(NextIs(Token::T_WHILE))
	{
		return LoopStm();
	}
	if(NextIs(Token::T_RETURN))
	{
		return ReturnStm();
	}
	if(NextIs(Token::T_READ))
	{
		return InputStm();
	}
	if(NextIs(Token::T_WRITE))
	{
		return OutputStm();
	}
	if(NextIs(Token::T_ID ))
	{
		Token id = Match(Token::T_ID);
		temp_name = id.value .charValue ;
		return AssCall();
	}
	error("line[%d] 你不是我认识的语句类型.", lineno);
}

SNL_Node *AssCall()
{
	if(NextIs(Token::T_ASSIGN ) || NextIs(Token::T_L_FKH ) || NextIs(Token::T_DOT)) return AssignmentRest();
	if(NextIs(Token::T_L_XKH)) return CallStmRest();
	error("line[%d] 这不是我的语法，既不像赋值，又不是过程调用.", lineno);
}

SNL_Node *AssignmentRest()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::StmtK;
	t->kind .stmt = SNL_Node::AssignK;
	
	SNL_Node *p = new SNL_Node();
	p->nodekind = SNL_Node::Expk;
	p->kind.exp = SNL_Node::IdKK;
	p->attr.expAttr.varkind = SNL_Node::IdV;
	p->name.push_back(temp_name);
	VariMore(p);
	t->child[0] = p;
	Match(Token::T_ASSIGN);
	t->child[1] = Exp();
	return t;
}

SNL_Node* ConditionalStm()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::StmtK;
	t->kind .stmt = SNL_Node::IfK;

	Match(Token::T_IF);

	t->child[0] = RelExp();

	Match(Token::T_THEN );

	SNL_Node *ttt = new SNL_Node();
	ttt->nodekind = SNL_Node::StmLK;
	ttt->child[0] = StmList();

	t->child[1] = ttt;

	if(NextIs(Token::T_ELSE ))
	{
		Match(Token::T_ELSE );
		SNL_Node *ppp = new SNL_Node();
		ppp->nodekind = SNL_Node::StmLK;
		ppp->child[0] = StmList();
		t->child[2] = ppp;
	}

	Match(Token::T_FI );

	return t;
}

SNL_Node* RelExp()
{
	SNL_Node *ret = Exp();

	if(ret->nodekind == SNL_Node::Expk 
			&& ret->kind.exp == SNL_Node::OpK 
			&& (ret->attr .expAttr .op == SNL_Node::LT || ret->attr .expAttr .op == SNL_Node::EQ))
	{
		return ret;
	}
	else
		error("line[%d] 你并不是条件表达式.", lineno);
}

SNL_Node* LoopStm()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::StmtK;
	t->kind .stmt = SNL_Node::WhileK;
	Match(Token::T_WHILE );

	t->child[0] = RelExp();

	Match(Token::T_DO );

	SNL_Node *ttt = new SNL_Node();
	ttt->nodekind = SNL_Node::StmLK;
	ttt->child[0] = StmList();

	t->child[1] = ttt;

	Match(Token::T_ENDWH );

	return t;
}

SNL_Node* InputStm()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::StmtK;
	t->kind .stmt = SNL_Node::ReadK;

	Match(Token::T_READ);
	Match(Token::T_L_XKH );
	Token id = Match(Token::T_ID );
	t->name.push_back(id.value .charValue );
	Match(Token::T_R_XKH );
	return t;
}

SNL_Node* OutputStm()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::StmtK;
	t->kind .stmt = SNL_Node::WriteK;

	Match(Token::T_WRITE);
	Match(Token::T_L_XKH );
	t->child[0] = Exp();
	Match(Token::T_R_XKH );
	return t;
}

SNL_Node* ReturnStm()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::StmtK;
	t->kind .stmt = SNL_Node::ReturnK;

	Match(Token::T_RETURN );
	return t;
}

SNL_Node* CallStmRest()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::StmtK;
	t->kind .stmt = SNL_Node::CallK;
	
	SNL_Node *p = new SNL_Node();
	p->nodekind = SNL_Node::Expk;
	p->kind.exp = SNL_Node::IdKK;
	p->attr.expAttr .varkind = SNL_Node::IdV;
	p->name.push_back(temp_name);

	t->child[0] = p;

	Match(Token::T_L_XKH );
	t->child[1] = ActParamList();
	Match(Token::T_R_XKH );
	return t;
}

SNL_Node* ActParamList()
{
	Token a = tokenList[0];
	if(NextIs(Token::T_R_XKH )) return 0;
	if(NextIs(Token::T_ID ) || NextIs(Token::T_INTEGER_VALUE) || NextIs(Token::T_L_XKH ))
	{
		SNL_Node *t = Exp();
		if(t)
		{
			t->sibling = ActParamMore();
			return t;
		}
		else
		{
			return t;
		}
	}
	error("line[%d] 传的参数不对.", lineno);
}

SNL_Node* ActParamMore()
{
	if(NextIs(Token::T_R_XKH )) return 0;

	Match(Token::T_COMMA );

	return ActParamList();
}

SNL_Node *Exp()
{
	SNL_Node *t = Simple_exp();
	if(NextIs(Token::T_LT ) || NextIs(Token::T_EQ))
	{
		SNL_Node * p = new SNL_Node();
		p->nodekind = SNL_Node::Expk;
		p->kind.exp = SNL_Node::OpK;
		p->child[0] = t;

		Token op("");
		if(NextIs(Token::T_LT )) {op = Match(Token::T_LT); p->attr.expAttr.op = SNL_Node::LT;}
		else {op = Match(Token::T_EQ); p->attr.expAttr .op = SNL_Node::EQ;}
		t = p;
		t->child[1] = Simple_exp();
		return t;
	}
	else
	{
		return t;
	}
}

SNL_Node *Simple_exp()
{
	SNL_Node *t = Term();

	while(NextIs(Token::T_ADD) || NextIs(Token::T_SUB))
	{
		SNL_Node *p = new SNL_Node();
		p->nodekind = SNL_Node::Expk;
		p->kind.exp = SNL_Node::OpK;
		p->child[0] = t;
		
		Token op("");
		if(NextIs(Token::T_ADD )) {op = Match(Token::T_ADD); p->attr.expAttr .op = SNL_Node::PLUS;}
		else {op = Match(Token::T_SUB); p->attr.expAttr .op = SNL_Node::MINUS;}
		t = p;
		t->child[1] = Term();
	}
	return t;
}

SNL_Node *Term()
{
	SNL_Node *t = Factor();
	while(NextIs(Token::T_MUL) || NextIs(Token::T_DIV))
	{
		SNL_Node *p = new SNL_Node();
		p->nodekind = SNL_Node::Expk;
		p->kind.exp = SNL_Node::OpK;
		p->child[0] = t;
		
		Token op("");
		if(NextIs(Token::T_MUL )) {op = Match(Token::T_MUL); p->attr.expAttr .op = SNL_Node::TIMES;}
		else {op = Match(Token::T_DIV); p->attr.expAttr .op = SNL_Node::OVER;}
		t = p;
		t->child[1] = Factor();
	}
	return t;
}

SNL_Node *Factor()
{
	if(NextIs(Token::T_INTEGER_VALUE))
	{
		Token iv = Match(Token::T_INTEGER_VALUE);
		SNL_Node *p = new SNL_Node();
		p->nodekind = SNL_Node::Expk;
		p->kind.exp = SNL_Node::ConstK;
		p->attr .expAttr .val = iv.value .intValue ;
		return p;
	}
	if(NextIs(Token::T_ID))
	{
		return Variable();
	}
	if(NextIs(Token::T_L_XKH ))
	{
		Match(Token::T_L_XKH);
		SNL_Node *t = Exp();
		Match(Token::T_R_XKH);
		return t;
	}
	error("line[%d] 因子[%s]不对.", lineno, NEXTTOKEN);
}

SNL_Node *Variable()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::Expk;
	t->kind.exp = SNL_Node::IdKK;
	t->attr.expAttr.varkind = SNL_Node::IdV;
	Token id = Match(Token::T_ID);
	t->name.push_back(id.value .charValue );
	VariMore(t);
	return t;
}

void VariMore(SNL_Node *t)
{
	if(NextIs(Token::T_ASSIGN )) return;
	if(NextIs(Token::T_MUL )) return;
	if(NextIs(Token::T_EQ )) return;
	if(NextIs(Token::T_LT )) return;
	if(NextIs(Token::T_SUB )) return;
	if(NextIs(Token::T_ADD )) return;
	if(NextIs(Token::T_DIV )) return;
	if(NextIs(Token::T_R_XKH )) return;
	if(NextIs(Token::T_R_FKH )) return;
	if(NextIs(Token::T_SEMICOLON )) return;
	if(NextIs(Token::T_COMMA )) return;
	if(NextIs(Token::T_THEN )) return;
	if(NextIs(Token::T_ELSE )) return;
	if(NextIs(Token::T_FI )) return;
	if(NextIs(Token::T_DO )) return;
	if(NextIs(Token::T_ENDWH )) return;
	if(NextIs(Token::T_END )) return;

	if(NextIs(Token::T_L_FKH ))
	{
		Match(Token::T_L_FKH);
		t->child[0] = Exp();
		t->attr.expAttr .varkind = SNL_Node::ArrayMembV;
		t->child[0]->attr.expAttr .varkind = SNL_Node::IdV;
		Match(Token::T_R_FKH);
		return;
	}
	else if(NextIs(Token::T_DOT ))
	{
		Match(Token::T_DOT );
		t->child[0] = Fieldvar();
		t->attr.expAttr .varkind = SNL_Node::FieldMembV;
		//t->child[0]->attr.expAttr .varkind = SNL_Node::IdV;
		return;
	}
	else
	{
		error("line[%d] 变量名的后续部分不对.", lineno);
	}
}

SNL_Node *Fieldvar()
{
	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::Expk;
	t->kind.exp = SNL_Node::IdKK;
	t->attr.expAttr .varkind = SNL_Node::IdV;
	Token id = Match(Token::T_ID);
	t->name.push_back(id.value .charValue );
	FieldvarMore(t);
	return t;
}

void FieldvarMore(SNL_Node *t)
{
	if(NextIs(Token::T_ASSIGN )) return;
	if(NextIs(Token::T_MUL )) return;
	if(NextIs(Token::T_EQ )) return;
	if(NextIs(Token::T_LT )) return;
	if(NextIs(Token::T_SUB )) return;
	if(NextIs(Token::T_ADD )) return;
	if(NextIs(Token::T_DIV )) return;
	if(NextIs(Token::T_R_XKH )) return;
	if(NextIs(Token::T_SEMICOLON )) return;
	if(NextIs(Token::T_COMMA )) return;
	if(NextIs(Token::T_THEN )) return;
	if(NextIs(Token::T_ELSE )) return;
	if(NextIs(Token::T_FI )) return;
	if(NextIs(Token::T_DO )) return;
	if(NextIs(Token::T_ENDWH )) return;
	if(NextIs(Token::T_END )) return;
	if(NextIs(Token::T_L_FKH ))
	{
		Match(Token::T_L_FKH);
		t->child[0] = Exp();
		t->attr.expAttr .varkind = SNL_Node::ArrayMembV;
		t->child[0]->attr.expAttr .varkind = SNL_Node::IdV;
		Match(Token::T_R_FKH);
		return;
	}
	else
	{
		error("%s 后边跟着一个不合适的东西.", t->name [0].c_str());
	}
}




Token current("");

Token Match(TokenType type)
{
	int size = tokenList.size();
	MyString theType = tokenList[0].type;
	if(tokenList.size()>0 && tokenList[0].type == type)
	{
		Token ret = tokenList[0];
		tokenList.erase(tokenList.begin());
		lineno = ret.lineno ;
		if(tokenList.size()>0)
			current = tokenList[0];
		return ret;
	}
	else
	{
		if(tokenList.size()>0)
			error("line[%d] 我想找%s, 不想要%s.", lineno, type.c_str (), NEXTTOKEN);
		else
			error("line[%d] 我在等待 %s, 但却没更多Token了.", lineno, type.c_str ());
	}
}



bool NextIs(TokenType type)
{
	return tokenList.size()>0 && tokenList[0].type == type;
}

SNL_Node *ProcMore()
{
	if(NextIs(Token::T_PROCEDURE ))
	{
		return ProcDeclaration();
	}
	return 0;
}