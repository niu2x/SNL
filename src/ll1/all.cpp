#include <vector>
#include "../snl/snl_node.h"
#include "../snl/Token.h"
#include "../MyString/MyString.h"
#include <stack>
#include "../general/error.h"
#include <assert.h>
#include "NT.h"
#include "table.h"
static int lineno = 1;
extern std::vector<Token> tokenList;

Token Match(TokenType);
bool NextIs(TokenType);
Token current("");

std::stack<SNL_Node **> yfsz;  //语法树


const int T_T = 0;
const int T_NT = 1;
class TNT
{
public:
	int type;          // 0 t,  1 nt
	TokenType t;
	enum NT_T nt;
	TNT(){}
	TNT(TokenType t):t(t), type(T_T){}
	TNT(enum NT_T nt):nt(nt), type(T_NT){}
};

std::stack<TNT> fhz;    

std::stack<SNL_Node *> czfz;

std::stack<SNL_Node *> czsz;


bool NextIs(TokenType type)
{
	return tokenList.size()>0 && tokenList[0].type == type;
}

Token PeekToken()
{
	assert(tokenList.size() > 0);
	return tokenList[0];
}

Token ReadToken()
{
	if(tokenList.size()>0)
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
		error("line[%d] Token不够.", lineno);
	}
}

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
			error("line[%d] 我想找%s, 不想要%s.", lineno, type.c_str (), tokenList[0].type == Token::T_ID ? tokenList[0].value.charValue.c_str():tokenList[0].type.c_str());
		else
			error("line[%d] 我在等待 %s, 但却没更多Token了.", lineno, type.c_str ());
	}
}

SNL_Node *parseLL();
void predict(int);
int Priosity(int);
void process1();
void process2();
void process3();
void process4();
void process5();
void process6();
void process7();
void process8();
void process9();
void process10();
void process11();
void process12();
void process13();
void process14();
void process15();
void process16();
void process17();
void process18();
void process19();
void process20();
void process21();
void process22();
void process23();
void process24();
void process25();
void process26();
void process27();
void process28();
void process29();
void process30();
void process31();
void process32();
void process33();
void process34();
void process35();
void process36();
void process37();
void process38();
void process39();
void process40();
void process41();
void process42();
void process43();
void process44();
void process45();
void process46();
void process47();
void process48();
void process49();
void process50();
void process51();
void process52();
void process53();
void process54();
void process55();
void process56();
void process57();
void process58();
void process59();
void process60();
void process61();
void process62();
void process63();
void process64();
void process65();
void process66();
void process67();
void process68();
void process69();
void process70();
void process71();
void process72();
void process73();
void process74();
void process75();
void process76();
void process77();
void process78();
void process79();
void process80();
void process81();
void process82();
void process83();
void process84();
void process85();
void process86();
void process87();
void process88();
void process89();
void process90();
void process91();
void process92();
void process93();
void process94();
void process95();
void process96();
void process97();
void process98();
void process99();
void process100();
void process101();
void process102();
void process103();
void process104();

SNL_Node *currentP = 0;
SNL_Node *parseLL()
{
	init_table();
	
	fhz.push(NT_Program);

	SNL_Node *root = new SNL_Node();
	currentP = root;
	currentP ->nodekind = SNL_Node::Prok;

	yfsz.push(&(currentP->child[2]));
	yfsz.push(&(currentP->child[1]));
	yfsz.push(&(currentP->child[0]));

	while(tokenList.size() > 0 || fhz.size() > 0)
	{
		if(fhz.size() == 0) error("line[%d] 程序的末尾太长了.", lineno);

		if(fhz.top().type == T_T)
		{
			Match(fhz.top().t);
			fhz.pop();
		}
		else
		{
			Token token = PeekToken();
			TNT tnt = fhz.top();
			std::map<TokenType, int> temp = table[fhz.top().nt];
			std::map<TokenType, int>::iterator it = temp.find(token.type);
			int pnum = -1;
			if(it != temp.end())
			{
				pnum = (*it).second;
			}

			if(pnum == -1)
			{
				error("line[%d] 正在处理非终结符%s, 但遇到的终结符[%s]不在此非终极符的predict集里.", lineno, nt_names[fhz.top().nt], token.type.c_str());
			}

			fhz.pop();

			predict(pnum);
		}
	}

	return root;
}

void predict(int pnum)
{
	switch(pnum)
	{
		case 1:
			 process1();
		break;
		case 2:
			 process2();
		break;
		case 3:
			 process3();
		break;
		case 4:
			 process4();
		break;
		case 5:
			 process5();
		break;
		case 6:
			 process6();
		break;
		case 7:
			 process7();
		break;
		case 8:
			 process8();
		break;
		case 9:
			 process9();
		break;
		case 10:
			 process10();
		break;
		case 11:
			 process11();
		break;
		case 12:
			 process12();
		break;
		case 13:
			 process13();
		break;
		case 14:
			 process14();
		break;
		case 15:
			 process15();
		break;
		case 16:
			 process16();
		break;
		case 17:
			 process17();
		break;
		case 18:
			 process18();
		break;
		case 19:
			 process19();
		break;
		case 20:
			 process20();
		break;
		case 21:
			 process21();
		break;
		case 22:
			 process22();
		break;
		case 23:
			 process23();
		break;
		case 24:
			 process24();
		break;
		case 25:
			 process25();
		break;
		case 26:
			 process26();
		break;
		case 27:
			 process27();
		break;
		case 28:
			 process28();
		break;
		case 29:
			 process29();
		break;
		case 30:
			 process30();
		break;
		case 31:
			 process31();
		break;
		case 32:
			 process32();
		break;
		case 33:
			 process33();
		break;
		case 34:
			 process34();
		break;
		case 35:
			 process35();
		break;
		case 36:
			 process36();
		break;
		case 37:
			 process37();
		break;
		case 38:
			 process38();
		break;
		case 39:
			 process39();
		break;
		case 40:
			 process40();
		break;
		case 41:
			 process41();
		break;
		case 42:
			 process42();
		break;
		case 43:
			 process43();
		break;
		case 44:
			 process44();
		break;
		case 45:
			 process45();
		break;
		case 46:
			 process46();
		break;
		case 47:
			 process47();
		break;
		case 48:
			 process48();
		break;
		case 49:
			 process49();
		break;
		case 50:
			 process50();
		break;
		case 51:
			 process51();
		break;
		case 52:
			 process52();
		break;
		case 53:
			 process53();
		break;
		case 54:
			 process54();
		break;
		case 55:
			 process55();
		break;
		case 56:
			 process56();
		break;
		case 57:
			 process57();
		break;
		case 58:
			 process58();
		break;
		case 59:
			 process59();
		break;
		case 60:
			 process60();
		break;
		case 61:
			 process61();
		break;
		case 62:
			 process62();
		break;
		case 63:
			 process63();
		break;
		case 64:
			 process64();
		break;
		case 65:
			 process65();
		break;
		case 66:
			 process66();
		break;
		case 67:
			 process67();
		break;
		case 68:
			 process68();
		break;
		case 69:
			 process69();
		break;
		case 70:
			 process70();
		break;
		case 71:
			 process71();
		break;
		case 72:
			 process72();
		break;
		case 73:
			 process73();
		break;
		case 74:
			 process74();
		break;
		case 75:
			 process75();
		break;
		case 76:
			 process76();
		break;
		case 77:
			 process77();
		break;
		case 78:
			 process78();
		break;
		case 79:
			 process79();
		break;
		case 80:
			 process80();
		break;
		case 81:
			 process81();
		break;
		case 82:
			 process82();
		break;
		case 83:
			 process83();
		break;
		case 84:
			 process84();
		break;
		case 85:
			 process85();
		break;
		case 86:
			 process86();
		break;
		case 87:
			 process87();
		break;
		case 88:
			 process88();
		break;
		case 89:
			 process89();
		break;
		case 90:
			 process90();
		break;
		case 91:
			 process91();
		break;
		case 92:
			 process92();
		break;
		case 93:
			 process93();
		break;
		case 94:
			 process94();
		break;
		case 95:
			 process95();
		break;
		case 96:
			 process96();
		break;
		case 97:
			 process97();
		break;
		case 98:
			 process98();
		break;
		case 99:
			 process99();
		break;
		case 100:
			 process100();
		break;
		case 101:
			 process101();
		break;
		case 102:
			 process102();
		break;
		case 103:
			 process103();
		break;
		case 104:
			 process104();
		break;
		default:
			error("line[%d] shit.", lineno);
	}
}

int Priosity(int tt)
{

	SNL_Node::OPOP t = (SNL_Node::OPOP)tt;
	if(t == SNL_Node::S_END)
	{
		return -1;
	}
	else if(t == SNL_Node::LKH)
	{
		return 0;
	}
	else if(t == SNL_Node::LT )
	{
		return 1;
	}
	else if(t == SNL_Node::EQ )
	{
		return 1;
	}
	else if(t == SNL_Node::PLUS )
	{
		return 2;
	}
	else if(t == SNL_Node::MINUS )
	{
		return 2;
	}
	else if(t == SNL_Node::TIMES )
	{
		return 3;
	}
	else if(t == SNL_Node::OVER )
	{
		return 3;
	}
	else
	{
		error("line[%d] shit.", lineno);
	}
}

void process1()
{
	fhz.push(Token::T_DOT);
	fhz.push(NT_ProgramBody);
	fhz.push(NT_DeclarePart);
	fhz.push(NT_ProgramHead);
}

void process2()
{
	fhz.push(NT_ProgramName);
	fhz.push(Token::T_PROGRAM);
	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::PheadK;
	SNL_Node ** p = yfsz.top();
	yfsz.pop();
	*p = currentP;
}

void process3()
{
	fhz.push(Token::T_ID);
	currentP->name.push_back(current.value .charValue );
}

void process4()
{
	fhz.push(NT_ProcDecpart);
	fhz.push(NT_VarDecpart);
	fhz.push(NT_TypeDecpart);
}

void process5()
{

}

void process6()
{
	fhz.push(NT_TypeDec);
}

void process7()
{
	fhz.push(NT_TypeDecList);
	fhz.push(Token::T_TYPE );
	currentP = new SNL_Node();
	currentP ->nodekind = SNL_Node::TypeK;
	SNL_Node **p = yfsz.top();
	yfsz.pop();
	*p = currentP;
	yfsz.push(&(currentP->sibling));
	yfsz.push(&(currentP->child[0]));
}

void process8()
{
	fhz.push(NT_TypeDecMore);
	fhz.push(Token::T_SEMICOLON );
	fhz.push(NT_TypeDef);
	fhz.push(Token::T_EQ);
	fhz.push(NT_TypeId);

	currentP = new SNL_Node();
	currentP ->nodekind = SNL_Node::DecK;

	SNL_Node ** p = yfsz.top();
	yfsz.pop();
	*p = currentP;

	yfsz.push(&(currentP->sibling ));
}

void process9()
{
	yfsz.pop();
}

void process10()
{
	fhz.push(NT_TypeDecList);
}

void process11()
{
	fhz.push(Token::T_ID );
	currentP->name.push_back(current.value .charValue );
}

SNL_Node::KINDDEC* temp = 0;

void process12()
{
	fhz.push(NT_BaseType);
	temp = &(currentP->kind .dec );
}

void process13()
{
	fhz.push(NT_StructureType);
}

void process14()
{
	currentP->kind.dec = SNL_Node::IdK;
	fhz.push(Token::T_ID);
	currentP->type_name.push_back(current.value .charValue);
}

void process15()
{
	fhz.push(Token::T_INTEGER);
	*temp = SNL_Node::IntegerK;
}

void process16()
{
	fhz.push(Token::T_CHAR);
	*temp = SNL_Node::CharK;
}

void process17()
{
	fhz.push(NT_ArrayType);
}

void process18()
{
	fhz.push(NT_RecordType);
}

void process19()
{
	fhz.push(NT_BaseType);
	fhz.push(Token::T_OF );
	fhz.push(Token::T_R_FKH );
	fhz.push(NT_Up);
	fhz.push(Token::T_RANGE );
	fhz.push(NT_Low);
	fhz.push(Token::T_L_FKH );
	fhz.push(Token::T_ARRAY );
	currentP->kind.dec = SNL_Node::ArrayK;
	temp = &(currentP->attr .arrayAttr .childType );
}

void process20()
{
	fhz.push(Token::T_INTEGER_VALUE );
	currentP->attr .arrayAttr .low = current.value .intValue ;
}

void process21()
{
	fhz.push(Token::T_INTEGER_VALUE );
	currentP->attr .arrayAttr .up = current.value .intValue ;
}

SNL_Node *temp2 = 0;
void process22()
{
	fhz.push(Token::T_END );
	fhz.push(NT_FieldDecList);
	fhz.push(Token::T_RECORD );
	currentP->kind .dec = SNL_Node::RecordK;
	temp2 = currentP;
	yfsz.push(&(currentP->child[0]));
}

void process23()
{
	fhz.push(NT_FieldDecMore);
	fhz.push(Token::T_SEMICOLON );
	fhz.push(NT_IdList);
	fhz.push(NT_BaseType);
	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::DecK;
	SNL_Node **t = yfsz.top();
	yfsz.pop();
	*t = currentP;
	temp = &(currentP->kind .dec );
	yfsz.push(&(currentP->sibling ));
}

void process24()
{
	fhz.push(NT_FieldDecMore);
	fhz.push(Token::T_SEMICOLON );
	fhz.push(NT_IdList);
	fhz.push(NT_ArrayType);
	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::DecK;
	SNL_Node **t = yfsz.top();
	yfsz.pop();
	*t = currentP;
	yfsz.push(&(currentP->sibling ));
}

void process25()
{
	yfsz.pop();
	currentP = temp2;
}

void process26()
{
	fhz.push(NT_FieldDecList);
}
void process27()
{
	fhz.push(NT_IdMore);
	fhz.push(Token::T_ID);
	currentP->name.push_back(current.value .charValue );
}

void process28()
{

}

void process29()
{
	fhz.push(NT_IdList);
	fhz.push(Token::T_COMMA );
}

void process30()
{

}

void process31()
{
	fhz.push(NT_VarDec);
}

void process32()
{
	fhz.push(NT_VarDecList);
	fhz.push(Token::T_VAR);
	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::VarK;
	SNL_Node **t = yfsz.top();
	yfsz.pop();
	*t = currentP;
	yfsz.push(&(currentP->sibling));
	yfsz.push(&(currentP->child[0]));
}

void process33()
{
	fhz.push(NT_VarDecMore);
	fhz.push(Token::T_SEMICOLON );
	fhz.push(NT_VarIdList);
	fhz.push(NT_TypeDef);
	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::DecK;
	SNL_Node **t = yfsz.top();
	yfsz.pop();
	*t = currentP;
	yfsz.push(&(currentP->sibling));
}

void process34()
{
	yfsz.pop();
}

void process35()
{
	fhz.push(NT_VarDecList);
}

void process36()
{
	fhz.push(NT_IdMore);
	fhz.push(Token::T_ID);
	currentP->name.push_back(current.value .charValue );
}

void process37()
{

}

void process38()
{
	fhz.push(NT_VarIdList);
	fhz.push(Token::T_COMMA);
}

void process39()
{

}

void process40()
{
	fhz.push(NT_ProcDec);
}

void process41()
{
	fhz.push(NT_ProcDecMore);
	fhz.push(NT_ProcBody);
	fhz.push(NT_ProcDecPart);
	fhz.push(Token::T_SEMICOLON );
	fhz.push(Token::T_R_XKH );
	fhz.push(NT_ParamList);
	fhz.push(Token::T_L_XKH );
	fhz.push(NT_ProcName);
	fhz.push(Token::T_PROCEDURE );

	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::ProcDecK;

	SNL_Node **t = yfsz.top();
	yfsz.pop();
	*t = currentP;


	yfsz.push(&(currentP->sibling));
	yfsz.push(&(currentP->child[2]));
	yfsz.push(&(currentP->child[1]));
	yfsz.push(&(currentP->child[0]));

	temp2 = currentP; //自己添加的
}

void process42()
{

}

void process43()
{
	fhz.push(NT_ProcDec);
}
void process44()
{
	fhz.push(Token::T_ID );
	currentP->name.push_back(current.value .charValue );
}

void process45()
{
	yfsz.pop();
}

void process46()
{
	fhz.push(NT_ParamDecList);
}

void process47()
{
	fhz.push(NT_ParamMore);
	fhz.push(NT_Param);
}

void process48()
{
	yfsz.pop();
	currentP = temp2;
}

void process49()
{
	fhz.push(NT_ParamDecList);
	fhz.push(Token::T_SEMICOLON );
}

void process50()
{
	fhz.push(NT_FormList);
	fhz.push(NT_TypeDef);
	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::DecK;
	currentP->attr .procAttr.paramt = SNL_Node::valparamtype;
	SNL_Node **t = yfsz.top();
	yfsz.pop();
	*t = currentP;
	yfsz.push(&(currentP->sibling));	
}

void process51()
{
	fhz.push(NT_FormList);
	fhz.push(NT_TypeDef);
	fhz.push(Token::T_VAR);
	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::DecK;
	currentP->attr .procAttr.paramt = SNL_Node::varparamtype;
	SNL_Node **t = yfsz.top();
	yfsz.pop();
	*t = currentP;
	yfsz.push(&(currentP->sibling));
}

void process52()
{
	fhz.push(NT_FidMore);
	fhz.push(Token::T_ID);
	currentP->name.push_back(current.value .charValue );
}

void process53()
{

}

void process54()
{
	fhz.push(NT_FormList);
	fhz.push(Token::T_COMMA );
}

void process55()
{
	fhz.push(NT_DeclarePart);
}

void process56()
{
	fhz.push(NT_ProgramBody);
}

void process57()
{
	fhz.push(Token::T_END);
	fhz.push(NT_StmList);
	fhz.push(Token::T_BEGIN);

	yfsz.pop();

	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::StmLK;

	SNL_Node **t = yfsz.top();
	yfsz.pop();
	*t = currentP;

	yfsz.push(&(currentP->child[0]));
}

void process58()
{
	fhz.push(NT_StmMore);
	fhz.push(NT_Stm);
}

void process59()
{
	yfsz.pop();
}

void process60()
{
	fhz.push(NT_StmList);
	fhz.push(Token::T_SEMICOLON);
}

void process61()
{
	fhz.push(NT_ConditionalStm);
	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::StmtK;
	currentP->kind.stmt = SNL_Node::IfK;
	SNL_Node **t = yfsz.top();
	yfsz.pop();
	*t = currentP;
	yfsz.push(&(currentP->sibling));
}

void process62()
{
	fhz.push(NT_LoopStm);
	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::StmtK;
	currentP->kind.stmt = SNL_Node::WhileK;
	SNL_Node **t = yfsz.top();
	yfsz.pop();
	*t = currentP;
	yfsz.push(&(currentP->sibling));
}

void process63()
{
	fhz.push(NT_InputStm);
	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::StmtK;
	currentP->kind.stmt = SNL_Node::ReadK;
	SNL_Node **t = yfsz.top();
	yfsz.pop();
	*t = currentP;
	yfsz.push(&(currentP->sibling));
}

void process64()
{
	fhz.push(NT_OutputStm);
	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::StmtK;
	currentP->kind.stmt = SNL_Node::WriteK;
	SNL_Node **t = yfsz.top();
	yfsz.pop();
	*t = currentP;
	yfsz.push(&(currentP->sibling));
}

void process65()
{
	fhz.push(NT_ReturnStm);
	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::StmtK;
	currentP->kind.stmt = SNL_Node::ReturnK;
	SNL_Node **t = yfsz.top();
	yfsz.pop();
	*t = currentP;
	yfsz.push(&(currentP->sibling));
}

void process66()
{
	fhz.push(NT_AssCall);
	fhz.push(Token::T_ID);

	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::StmtK;

	SNL_Node *t = new SNL_Node();
	t->nodekind = SNL_Node::Expk;
	t->kind.exp = SNL_Node::IdKK;
	t->attr.expAttr .varkind = SNL_Node::IdV;
	t->name.push_back(current.value .charValue );
	currentP->child[0] = t;

	SNL_Node **t1 = yfsz.top();
	yfsz.pop();
	*t1 = currentP;

	yfsz.push(&(currentP->sibling));
}

void process67()
{
	fhz.push(NT_AssignmentRest);
	currentP->kind .stmt = SNL_Node::AssignK;
}

void process68()
{
	fhz.push(NT_CallStmRest);
//	currentP->attr .expAttr .varkind = SNL_Node::IdV;
	currentP->kind.stmt = SNL_Node::CallK;
}

void process69()
{
	fhz.push(NT_Exp);
	fhz.push(Token::T_ASSIGN );
	fhz.push(NT_VariMore);

	yfsz.push(&(currentP->child[1]));
	currentP=currentP->child[0];

	SNL_Node *end = new SNL_Node();
	end->nodekind = SNL_Node::Expk;
	end->kind .exp = SNL_Node::OpK;
	end->attr .expAttr .op = SNL_Node::S_END;
	czfz.push(end);
}

void process70()
{
	fhz.push(Token::T_FI);
	fhz.push(NT_StmList);
	fhz.push(Token::T_ELSE );
	fhz.push(NT_StmList);
	fhz.push(Token::T_THEN );
	fhz.push(NT_RelExp);
	fhz.push(Token::T_IF);

	currentP->child[1] = new SNL_Node();
	currentP->child[1]->nodekind = SNL_Node::StmLK;

	currentP->child[2] = new SNL_Node();
	currentP->child[2]->nodekind = SNL_Node::StmLK;

	yfsz.push(&(currentP->child[2]->child[0]));
	yfsz.push(&(currentP->child[1]->child[0]));
	yfsz.push(&(currentP->child[0]));
}

void process71()
{
	fhz.push(Token::T_ENDWH);
	fhz.push(NT_StmList);
	fhz.push(Token::T_DO );
	fhz.push(NT_RelExp);
	fhz.push(Token::T_WHILE);

	currentP->child[1] = new SNL_Node();
	currentP->child[1]->nodekind = SNL_Node::StmLK;

	yfsz.push(&(currentP->child[1]->child[0]));
	yfsz.push(&(currentP->child[0]));
}

void process72()
{
	fhz.push(Token::T_R_XKH );
	fhz.push(NT_Invar);
	fhz.push(Token::T_L_XKH);
	fhz.push(Token::T_READ );
}

void process73()
{
	fhz.push(Token::T_ID);
	currentP->name.push_back(current.value .charValue );
}

void process74()
{
	fhz.push(Token::T_R_XKH );
	fhz.push(NT_Exp);
	fhz.push(Token::T_L_XKH);
	fhz.push(Token::T_WRITE );
	yfsz.push(&(currentP->child[0]));

	SNL_Node *end = new SNL_Node();
	end->nodekind = SNL_Node::Expk;
	end->kind .exp = SNL_Node::OpK;
	end->attr .expAttr .op = SNL_Node::S_END;
	czfz.push(end);
}

void process75()
{
	fhz.push(Token::T_RETURN );
}

void process76()
{
	fhz.push(Token::T_R_XKH );
	fhz.push(NT_ActParamList);
	fhz.push(Token::T_L_XKH);
	yfsz.push(&(currentP->child[1]));

}

void process77()
{
	yfsz.pop();
}

void process78()
{
	fhz.push(NT_ActParamMore);
	fhz.push(NT_Exp);

	SNL_Node *end = new SNL_Node();
	end->nodekind = SNL_Node::Expk;
	end->kind .exp = SNL_Node::OpK;
	end->attr .expAttr .op = SNL_Node::S_END;
	czfz.push(end);
}

void process79()
{

}

void process80()
{
	fhz.push(NT_ActParamList);
	fhz.push(Token::T_COMMA);
	yfsz.push(&(currentP->sibling ));
}

bool getExpResult = true;

void process81()
{
	fhz.push(NT_OtherRelE);
	fhz.push(NT_Exp);

	getExpResult = false;

	SNL_Node *end = new SNL_Node();
	end->nodekind = SNL_Node::Expk;
	end->kind .exp = SNL_Node::OpK;
	end->attr .expAttr .op = SNL_Node::S_END;
	czfz.push(end);
}

void process82()
{
	fhz.push(NT_Exp);
	fhz.push(NT_CmpOp);

	currentP = new SNL_Node();
	currentP->nodekind = SNL_Node::Expk;
	currentP->kind .exp = SNL_Node::OpK;

	if(current.type == Token::T_LT)
		currentP->attr .expAttr .op = SNL_Node::LT;
	else
		currentP->attr .expAttr .op = SNL_Node::EQ;

	while(Priosity((czfz.top())->attr.expAttr.op) >= Priosity(currentP->attr .expAttr .op))
	{
		SNL_Node *t = czfz.top();
		czfz.pop();

		SNL_Node *r = czsz.top(); czsz.pop();
		SNL_Node *l = czsz.top(); czsz.pop();
		
		t->child[0] = l;
		t->child[1] = r;
		czsz.push(t);
	}

	czfz.push(currentP);

	getExpResult = true;
}

int expflag = 0;
bool getExpResult2 = false;

void process83()
{
	fhz.push(NT_OtherTerm);
	fhz.push(NT_Term);
}

void process84()
{
	if(current.type == Token::T_R_XKH && expflag != 0)
	{
		while((czfz.top())->attr.expAttr.op != SNL_Node::LKH)
		{
			SNL_Node * t=czfz.top(); czfz.pop();
			SNL_Node * r=czsz.top(); czsz.pop();
			SNL_Node * l=czsz.top(); czsz.pop();
			t->child[0] = l;
			t->child[1] = r;
			czsz.push(t);
		}
		delete czfz.top();
		czfz.pop();
		expflag -= 1;
	}
	else
	{
		if(getExpResult == true || getExpResult2 == true)
		{
			while((czfz.top())->attr.expAttr.op != SNL_Node::S_END)
			{
				SNL_Node * t=czfz.top(); czfz.pop();
				SNL_Node * r=czsz.top(); czsz.pop();
				SNL_Node * l=czsz.top(); czsz.pop();
				t->child[0] = l;
				t->child[1] = r;
				czsz.push(t);
			}
			delete czfz.top();
			czfz.pop();

			currentP = czsz.top();
			czsz.pop();

			SNL_Node **t = yfsz.top();
			yfsz.pop();
			*t = currentP;
			getExpResult2 = false;
		}
	}
}

void process85()
{
	fhz.push(NT_Exp);
	fhz.push(NT_AddOp);
	currentP = new SNL_Node();
	currentP ->nodekind  = SNL_Node::Expk;
	currentP->kind .exp = SNL_Node::OpK;
	if(current.type == Token::T_ADD ) currentP->attr .expAttr .op = SNL_Node::PLUS;
	else currentP->attr .expAttr .op = SNL_Node::MINUS;
	while(Priosity((czfz.top())->attr.expAttr.op) >= Priosity(currentP->attr .expAttr .op))
	{		
		SNL_Node * t=czfz.top(); czfz.pop();
		SNL_Node * r=czsz.top(); czsz.pop();
		SNL_Node * l=czsz.top(); czsz.pop();
		t->child[0] = l;
		t->child[1] = r;
		czsz.push(t);
	}

	czfz.push(currentP);
}

void process86()
{
	fhz.push(NT_OtherFactor);
	fhz.push(NT_Factor);
}

void process87()
{
	
}

void process88()
{
	fhz.push(NT_Term);
	fhz.push(NT_MultOp);

	currentP = new SNL_Node();
	currentP ->nodekind  = SNL_Node::Expk;
	currentP->kind .exp = SNL_Node::OpK;
	if(current.type == Token::T_MUL ) currentP->attr .expAttr .op = SNL_Node::TIMES;
	else currentP->attr .expAttr .op = SNL_Node::OVER;
	
	while(Priosity((czfz.top())->attr.expAttr.op) >= Priosity(currentP->attr .expAttr .op))
	{		
		SNL_Node * t=czfz.top(); czfz.pop();
		SNL_Node * r=czsz.top(); czsz.pop();
		SNL_Node * l=czsz.top(); czsz.pop();
		t->child[0] = l;
		t->child[1] = r;
		czsz.push(t);
	}

	czfz.push(currentP);
}

void process89()
{
	fhz.push(Token::T_R_XKH );
	fhz.push(NT_Exp);
	fhz.push(Token::T_L_XKH );
	currentP = new SNL_Node();
	currentP ->nodekind  = SNL_Node::Expk;
	currentP->kind .exp = SNL_Node::OpK;
	currentP->attr .expAttr .op = SNL_Node::LKH;
	czfz.push(currentP);
	expflag +=1;
}

void process90()
{
	fhz.push(Token::T_INTEGER_VALUE );
	currentP = new SNL_Node();
	currentP ->nodekind  = SNL_Node::Expk;
	currentP->kind .exp = SNL_Node::ConstK;
	currentP->attr .expAttr .val = current.value .intValue ;
	czsz.push(currentP);
}

void process91()
{
	fhz.push(NT_Variable);
}

void process92()
{
	fhz.push(NT_VariMore);
	fhz.push(Token::T_ID);

	currentP = new SNL_Node();
	currentP ->nodekind  = SNL_Node::Expk;
	currentP->kind .exp = SNL_Node::IdKK;

	currentP->name.push_back(current.value .charValue );
	czsz.push(currentP);
}

void process93()
{
	currentP->attr .expAttr .varkind = SNL_Node::IdV;
}

void process94()
{
	fhz.push(Token::T_R_FKH );
	fhz.push(NT_Exp);
	fhz.push(Token::T_L_FKH );
	currentP->attr .expAttr .varkind = SNL_Node::ArrayMembV;
	yfsz.push(&(currentP->child[0]));
	getExpResult2 = true;
	SNL_Node *end = new SNL_Node();
	end->nodekind = SNL_Node::Expk;
	end->kind .exp = SNL_Node::OpK;
	end->attr .expAttr .op = SNL_Node::S_END;
	czfz.push(end);
}

void process95()
{
	fhz.push(NT_FieldVar);
	fhz.push(Token::T_DOT);
	currentP->attr .expAttr .varkind = SNL_Node::FieldMembV;
	yfsz.push(&(currentP->child[0]));
}

void process96()
{
	fhz.push(NT_FieldVarMore);
	fhz.push(Token::T_ID);

	currentP = new SNL_Node();
	currentP ->nodekind  = SNL_Node::Expk;
	currentP->kind .exp = SNL_Node::IdKK;

	currentP->name.push_back(current.value .charValue );

	SNL_Node **t = yfsz.top();
	yfsz.pop();

	*t = currentP;
}

void process97()
{
	currentP->attr.expAttr .varkind = SNL_Node::IdV;
}

void process98()
{
	process94();
}

void process99()
{
	fhz.push(Token::T_LT );
}

void process100()
{
	fhz.push(Token::T_EQ );
}

void process101()
{
	fhz.push(Token::T_ADD );
}

void process102()
{
	fhz.push(Token::T_SUB );
}

void process103()
{
	fhz.push(Token::T_MUL );
}

void process104()
{
	fhz.push(Token::T_DIV );
}