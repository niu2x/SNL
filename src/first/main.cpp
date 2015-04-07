#include "../MyString/MyString.h"
#include "../IO/StdinReader.h"
#include "../snl/token.h"
int main()
{
	MyString text = StdinReader().read();
	text = text.replace ("\r", " ");
	//text = text.replace ("\n", " ");
	//text = text.replace ("\t", " ");
	//text = text.replace ("	", " ");
	const int deliNumber = 21;
	MyString deli[deliNumber] = {"\t", ":=", "..", "+", "-", "*", "/", "<", "=", "(", ")", "[", "]", ".", ";", ",", " ", "\'", "{", "}", "\n"};

	MyStringList strlist = text.split2 (deli[0]);

	for(int k = 1; k < deliNumber; k++)
	{
		MyStringList temp;
		for(int i = 0; i < strlist.size(); i ++)
		{
			temp = temp + strlist[i].split2(deli[k]);
		}

		strlist = temp;
	}

	bool flag = false;  //是否遇到了单引号 ，遇到意味着 此后 不删除空格
	for(MyStringList::iterator it = strlist.begin(); it !=strlist.end() ; it ++)
	{	
		if(*it == "\'")
		{
			flag = !flag;
		}
		if(flag == false && (*it).is_space())
		{
			strlist.erase(it);
			it = strlist.begin();
		}
	}

	for(it = strlist.begin(); it !=strlist.end() ; it ++)             //去掉注释
	{
		if((*it) == "{")
		{
			for(MyStringList::iterator kk = it; kk !=strlist.end() ; kk ++)
			{
				if(*kk == "}")
					break;
			}
			if(kk != strlist.end())                       //it ~ kk 之间是注释
			{
				kk ++;

				MyString to_insert = "";
				for(MyStringList::iterator jj = it; jj != kk; jj++)   //查一查注释之间是否有换行符, 这样跨行注释 才能 保持行号的正确
				{
					if((*jj) == "\n")
					{
						to_insert = to_insert + "\n";
					}
				}
				MyStringList newline_list = to_insert.split2("\n");
				strlist.erase(it, kk);
				strlist.insert(it, newline_list.begin(), newline_list.end());
			}
			else
			{
				printf("Error, need a }\n");
				exit(1);
			}
		}
	}

	int current_line_number = 1;
	while(strlist.size()>0)
	{
		Token token = Token::check (strlist);
		if(token.type == Token::T_ERROR )
		{
			printf("Error: line %d, unknow token:%s\n", current_line_number, token.value.charValue .c_str ());
			exit(1);
		}
		else if(token.type == Token::T_NEWLINE)
		{
			current_line_number ++;
		}
		else
		{
			printf("%-4d%s%20s%s%8d%s%10s\n", current_line_number,token.delimiter.c_str (), token.type.c_str () ,token.delimiter.c_str (), token.value.intValue, token.delimiter.c_str (), token.value.charValue.c_str () );
		}
	}
	return 0;
}