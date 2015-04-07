#include "../MyString/MyString.h"

void error(char *str=0, ...)
{
	if(str == 0)
		printf("error.\n");
	else
		vprintf(str, (char *)((int)(&str)+4));
}

int main()
{
	MyString str("Hello World.");

	printf("str = %s\n", str.c_str());
	printf("len = %d\n", str.get_length());
	printf("count l = %d\n", str.count("l"));
	printf("count ll = %d\n", str.count("ll"));
	printf("start_with He %d\n", str.start_with("He"));
	printf("start_with e %d\n", str.start_with("e"));
	printf("end_with d %d\n", str.end_with("d"));
	printf("end_with d. %d\n", str.end_with("d."));
	printf("find ll %d\n", str.find("ll"));
	printf("rfind l %d\n", str.rfind("l"));
	printf("find Wd %d\n", str.find("Wd"));
	printf("rfind ls %d\n", str.rfind("ls"));
	printf("123 isnumber %d\n", MyString("123").is_number());
	printf("123s isnumber %d\n", MyString("123s").is_number());
	printf("123 isalpha %d\n", MyString("123").is_alpha());
	printf("sss isalpha %d\n", MyString("sss").is_alpha());
	printf("sss isspace %d\n", MyString("sss").is_space());
	printf(" isspace %d\n", MyString("\r\n\t ").is_space());

	str="1a2a3aa4a5a6";
	MyStringList strlist = str.split("a");
	for(int i = 0; i < strlist.size(); i ++)
	{
		printf("%s\n", strlist[i].c_str());
	}
	str = MyString("AA").join(strlist);
	printf("%s\n", str.c_str ());
	strlist = str.split2("AA");
	for(i = 0; i < strlist.size(); i ++)
	{
		printf("%s\n", strlist[i].c_str());
	}

	str = str + "ZZZZZZZZZZ";
	printf("%s\n", str.c_str ());
	printf("%s\n", str(0, 11111111).c_str ());
	printf("%s\n", str(0, -11111111).c_str ());
	printf("%s\n", str(5, 13).c_str ());
	printf("%s\n", str(2, 5).c_str ());
	printf("%d\n", str(2, 3).get_code ());
	printf("%s\n", str[2].c_str ());

	MyString aaaa="     6";
	aaaa = aaaa*3;
	printf("%s\n", aaaa.c_str ());
	printf("%s\n", aaaa.lstrip().c_str ());

	error("%d %s\n", 4, "666");
}
