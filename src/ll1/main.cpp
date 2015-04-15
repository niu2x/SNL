#include "../snl/Token.h"
#include "../IO/File.h"
#include "../IO/StdinReader.h"
#include <vector>
#include "../snl/outputTree.h"
#include "../snl/SNL_Node.h"
std::vector<Token> tokenList;
SNL_Node *parseLL();

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

	SNL_Node *root = parseLL();

	print(root);
	return 0;
}
