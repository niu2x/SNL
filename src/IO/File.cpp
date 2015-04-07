#include "File.h"
#include <stdio.h>
File::File(const MyString &filename):filename(filename)
{
}

MyString File::read ()
{
	FILE *fp = fopen(filename.c_str (), "rt");
	std::vector<char> chars;
	char c;
	while((c=fgetc(fp))!=-1)
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
	fclose(fp);
}
