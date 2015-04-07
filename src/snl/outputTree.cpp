#include "snl_node.h"
#include "..\\mystring\\mystring.h"

void printNC(int n, MyString s)
{
	for(int i=0; i < n; i ++)
		printf("%s", s.c_str ());
}
void process(SNL_Node *node, int level)
{
	MyString tab = "    ";
	printNC(level, tab);
	switch(node->nodekind )
	{
	case SNL_Node::Prok:
		printf("Prok\n");
		break;
	case SNL_Node::PheadK:		
		printf("PheadK %s\n", node->name[0].c_str());
		break;
	case SNL_Node::TypeK:	
		printf("TypeK\n");
		break;
	case SNL_Node::VarK:	
		printf("VarK\n");
		break;
	case SNL_Node::StmLK:
		printf("StmLK\n");
		break;
	case SNL_Node::DecK:
		{
			switch(node->kind .dec )
			{
			case SNL_Node::IntegerK:
				{
					if(node->attr.procAttr.paramt == SNL_Node::varparamtype)
					{
						printf("DecK Var Integer  ");
					}
					else
						printf("DecK Integer  ");
					for(int i = 0; i < node->name.size(); i ++)
					{
						printf("%s ", node->name[i].c_str());
					}
					printf("\n");
				}
				break;
			case SNL_Node::CharK:
				{
					if(node->attr.procAttr.paramt == SNL_Node::varparamtype)
					{
						printf("DecK Var Char  ");
					}
					else
						printf("DecK Char  ");
					for(int i = 0; i < node->name.size(); i ++)
					{
						printf("%s ", node->name[i].c_str());
					}
					printf("\n");
				}
				break;
			case SNL_Node::RecordK:
				{
					if(node->attr.procAttr.paramt == SNL_Node::varparamtype)
					{
						printf("DecK Var RecordK  ");
					}
					else
						printf("DecK RecordK  ");
					for(int i = 0; i < node->name.size(); i ++)
					{
						printf("%s ", node->name[i].c_str());
					}
					printf("\n");
				}
				break;
			case SNL_Node::IdK:
				{
					if(node->attr.procAttr.paramt == SNL_Node::varparamtype)
					{
						printf("DecK Var %s  ", node->type_name[0].c_str());
					}
					else
						printf("DecK %s  ", node->type_name[0].c_str());
					
					for(int i = 0; i < node->name.size(); i ++)
					{
						printf("%s ", node->name[i].c_str());
					}
					printf("\n");
				}
				break;
			case SNL_Node::ArrayK:
				{
					MyString childType;
					if(node->attr .arrayAttr .childType == SNL_Node::CharK) childType = "Char";
					else childType = "Integer";

					if(node->attr.procAttr.paramt == SNL_Node::varparamtype)
					{
						printf("DecK Var ArrayK [%d..%d] of %s  ", node->attr .arrayAttr .low , node->attr .arrayAttr .up ,  childType.c_str());
					}
					else
						printf("DecK ArrayK [%d..%d] of %s  ", node->attr .arrayAttr .low , node->attr .arrayAttr .up ,  childType.c_str());
					for(int i = 0; i < node->name.size(); i ++)
					{
						printf("%s ", node->name[i].c_str());
					}
					printf("\n");
				}
				break;
			}
		}
		break;
	case SNL_Node::StmtK:
		{
			printf("StmtK ");
			switch(node->kind .stmt )
			{
			case SNL_Node::IfK:
				printf("if\n");
				break;
			case SNL_Node::ReturnK:
				printf("return\n");
				break;
			case SNL_Node::WhileK:
				printf("while\n");
				break;
			case SNL_Node::CallK:
				printf("call\n");
				break;
			case SNL_Node::AssignK:
				printf("assign\n");
				break;
			case SNL_Node::ReadK:
				printf("read %s\n", node->name[0].c_str());
				break;
			case SNL_Node::WriteK:
				printf("write\n");
				break;
			}
		}
		break;
	case SNL_Node::Expk:
		printf("ExpK ");
		switch(node->kind.exp )
		{
		case SNL_Node::OpK:
			{
				char *op[] = {"<", "=", "+", "-", "*", "/"};
				printf("Op %s\n", op[node->attr .expAttr .op ]);
			}
			break;
		case SNL_Node::ConstK:
			{
				printf("Const %d\n",node->attr .expAttr .val );
			}
			break;
		case SNL_Node::IdKK:
			{
				//printf("IdKK %s\n",node->name[0].c_str());
				switch(node->attr.expAttr.varkind)
				{
				case SNL_Node::IdV:
					printf("IdV %s\n",node->name[0].c_str());
					break;
				case SNL_Node::ArrayMembV:
					printf("ArrayMembV %s\n",node->name[0].c_str());
					break;
				case SNL_Node::FieldMembV:
					printf("FieldMembV %s\n",node->name[0].c_str());
					break;
				}
			}
			break;
		}
		break;
	case SNL_Node::ProcDecK:
		printf("ProcDecK %s\n", node->name[0].c_str());
		break;
	}
}

void walk(SNL_Node *node, int level)
{
	if(node == 0) return;
	process(node, level);
	if(node->child[0]) walk(node->child[0], level+1);
	if(node->child[1]) walk(node->child[1], level+1);
	if(node->child[2]) walk(node->child[2], level+1);
	if(node->sibling) walk(node->sibling, level);
}

void print(SNL_Node *root)
{
	walk(root, 0);
}
