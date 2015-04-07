#include "StdinReader.h"
#include <vector>
MyString StdinReader::read ()
{
	std::vector<char> chars;
	char c;
	while((c=getchar())!=-1)
	{
		chars.push_back(c);
	}
	char *buf = new char[chars.size()+1];
	for(int i = 0; i < chars.size(); i ++)
	{
		buf[i] = chars[i];
	}
	buf[i] = 0;
	MyString ret(buf);
	delete []buf;
	return ret;
}