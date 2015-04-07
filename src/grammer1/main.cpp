#include "../Tree/Tree.h"
#include "../IO/StdinReader.h"
#include "../IO/File.h"
#include <vector>
#include "../snl/Token.h"

std::vector<Token> tokenList;

void error()
{
	printf("error\n");
	exit(1);
}
bool NextIs(TokenType type)
{
	return tokenList.size() > 0 && tokenList[0].type == type;
}


Token Match(TokenType type)
{
	if(tokenList.size() < 1)
	{
		error();
	}
	if(tokenList[0].type != type)
	{
		error();
	}

	Token ret = tokenList[0];
	
	tokenList.erase(tokenList.begin());

	return ret;
}

TreeNode TypeDef()
{
	if(NextIs(Token::T_INTEGER))
	{
		Match(Token::T_INTEGER);
		return TreeNode(TreeNode::TNT_TYPE, "integer");  //ÀàÐÍ×Ö·û´®
	}
	else if(NextIs(Token::T_CHAR))
	{
		Match(Token::T_CHAR);
		return TreeNode(TreeNode::TNT_TYPE, "char");
	}
	else if(NextIs(Token::T_ID))
	{
		Token id = Match(Token::T_ID);
		return TreeNode(TreeNode::TNT_TYPE, id.value .charValue );
	}
	else if(NextIs(Token::T_ARRAY))
	{
		return ArrayType();
	}
	else if(NextIs(Token::T_RECORD))
	{
		return RecType();
	}
	else
	{
		error();
	}
}

TreeNode OneTypeDec()
{
	TreeNode node(TreeNode::TNT_ONE_TYPE_DEC);

	Token newTypeID = Match(Token::T_ID);
	Match(Token::T_EQ);
	TreeNode typeDef= TypeDef();
	Match(Token::T_SEMICOLON);

	node.add_child (TreeNode::TNT_ID , newTypeID.value.charValue);
	node.add_child (typeDef);
}

TreeNode TypeDecpart()
{
	TreeNode node(TreeNode::TNT_ALL_TYPE_DEC);

	if(NextIs(Token::T_TYPE))
	{
		Match(Token::T_TYPE);
		do
		{
			TreeNode oneTypeDec = OneTypeDec();
			node.add_child (oneTypeDec);

		}while(NextIs(Token::T_ID));
		if(NextIs(Token::T_VAR) || NextIs(Token::T_PROCEDURE ) || NextIs(Token::T_BEGIN))
		{
			return node;
		}
		else
		{
			error();
		}
	}
	else if(NextIs(Token::T_VAR) || NextIs(Token::T_PROCEDURE ) || NextIs(Token::T_BEGIN))
	{
		return node;
	}
	else
	{
		error();
	}
}

TreeNode DeclarePart()
{
	TreeNode node(TreeNode::TNT_DECLARE_PART);

	TreeNode typeDecpart = TypeDecpart();
	TreeNode varDecpart = VarDecpart();
	TreeNode procDecpart = ProcDecpart();

	node.add_child (typeDecpart);
	node.add_child (varDecpart);
	node.add_child (procDecpart);
}
TreeNode ProgramHead()
{
	if(tokenList.size() == 0) 
	{
		printf("error");
		exit(0);
	}

	Match(Token::T_PROGRAM);
	Match(Token::T_ID);

	return TreeNode(TreeNode::TNT_PROGRAM_HEAD);
}
TreeNode Program()
{
	TreeNode node(TreeNode::TNT_PROGRAM);

	TreeNode programHead = ProgramHead();
	TreeNode declarePart = DeclarePart();
	TreeNode programBody = ProgramBody();

	node.add_child (programHead);
	node.add_child (declarePart);
	node.add_child (programBody);
	return node;
}

int main()
{
	MyStringList tokenText = File("../../2.txt").read().split("\n");
	for(MyStringList::iterator it = tokenText.begin(); it != tokenText.end(); it++)
	{
		MyStringList token_parts = (*it).split(Token::delimiter);
		tokenList.push_back(Token(token_parts[1], atoi(token_parts[2].c_str()), token_parts[3]));
	}

	TreeNode &program = Program();
	return 0;
}

