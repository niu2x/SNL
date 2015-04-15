#ifndef __myFile__
#define __myFile__
#include "../MyString/MyString.h"

class File
{
	MyString filename;
public:
	File(const MyString &filename);
	MyString read();

};
#endif