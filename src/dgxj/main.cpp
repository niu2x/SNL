#include "../snl/Token.h"
#include "all.h"
#include "../IO/File.h"
#include "../IO/StdinReader.h"
#include <vector>
std::vector<Token> tokenList;
#include "../snl/outputTree.h"

int main()
{
	MyString text = StdinReader().read ();

	MyStringList testList = text.split("\n");

	for(MyStringList::iterator it = testList.begin(); it != testList.end(); it++)
	{
		MyStringList token_parts = (*it).split(Token::delimiter);
		if(token_parts.size() == 4)
		{
			tokenList.push_back(Token(token_parts[1], atoi(token_parts[2].c_str()), token_parts[3], atoi(token_parts[0].c_str())));
		}
		else
		{
			tokenList.push_back(Token(token_parts[1], atoi(token_parts[2].c_str()), "", atoi(token_parts[0].c_str())));
		}
	}

	SNL_Node *root = Program();

	print(root);
	return 0;
}
