#include "MyString.h"
#include <assert.h>
#include <cmath>
int MyString::npos = std::string::npos;
MyString::MyString(const char *c_str)
{
	assert(c_str != 0);
	data = std::string(c_str);
}
MyString::~MyString ()
{
}
MyString::MyString(const MyString &it):data(it.data)
{
}
MyString& MyString::operator = (const MyString &it)
{
	if(this != &it)
	{
		data = it.data;
	}
	return *this;
}

int MyString::count (const MyString &str)const
{
	assert(str.get_length () > 0);
	int count = 0;
	int len = get_length();
	int pos = 0;
	while(pos < len)
	{
		int ret = data.find(str.data, pos);
		if(ret != std::string::npos)
		{
			count += 1;
			pos = ret + str.get_length ();
		}
		else
		{
			break;
		}
	}
	return count;
}

int MyString::get_length ()const
{
	return data.length ();
}

bool MyString::end_with(const MyString &str)const
{
	int ret = data.rfind (str.data);
	return ret + str.get_length () == get_length();
}

bool MyString::start_with(const MyString &str)const
{
	int ret = data.find (str.data);
	return ret == 0;
}

int MyString::find(const MyString &str, int pos)const
{
	return data.find (str.data, pos);
}
int MyString::rfind(const MyString &str, int pos)const
{
	return data.rfind (str.data, pos);
}
bool MyString::is_number()const
{
	for(int i = 0; i < get_length(); i ++)
	{
		MyString thisChar = sub_string(i, i+1);
		if (!(thisChar.get_code() <= '9' && thisChar.get_code() >= '0'))
		{
			return false;
		}
	}
	return true;
}
bool MyString::is_alpha_or_number()const
{
	for(int i = 0; i < get_length(); i ++)
	{
		MyString thisChar = sub_string(i, i+1);
		if ((!(thisChar.get_code() <= '9' && thisChar.get_code() >= '0')) && (!(thisChar.get_code() <= 'z' && thisChar.get_code() >= 'a')) && (!(thisChar.get_code() <= 'Z' && thisChar.get_code() >= 'A')))
		{
			return false;
		}
	}
	return true;
}
bool MyString::is_alpha()const
{
	for(int i = 0; i < get_length(); i ++)
	{
		MyString thisChar = sub_string(i, i+1);
		if (!((thisChar.get_code() <= 'z' && thisChar.get_code() >= 'a') || (thisChar.get_code() <= 'Z' && thisChar.get_code() >= 'A')))
		{
			return false;
		}
	}
	return true;
}

bool MyString::is_space()const
{
	MyString blank = MyString(" \t\r");
	for(int i = 0; i < get_length(); i ++)
	{
		MyString thisChar = sub_string(i, i+1);
		if (blank.find(thisChar) == npos)
		{
			return false;
		}
	}
	return true;
}

MyString MyString::join(const std::vector<MyString> &strs)const
{
	MyString ret("");
	
	std::vector<MyString>::const_iterator it = strs.begin();

	if(it != strs.end())
	{
		ret = ret + *it;
	}

	it ++;

	for(; it != strs.end(); it ++)
	{
		ret = ret + *this + *it;
	}
	
	return ret;
}

MyString MyString::replace(const MyString &oldStr, const MyString &newStr, int times)const
{
	int pos = -1;
	MyString ret(*this);
	int time = 0;
	while((pos = find(oldStr, pos+1)) != npos && (times == 0 || time < times))
	{
		ret = ret.sub_string(0, pos) + newStr + ret.sub_string(pos + oldStr.get_length (), get_length());
		time ++;
	}
	return ret;
}
std::vector<MyString> MyString::split(const MyString &str)const
{	
	std::vector<MyString> ret;
	int pos = 0;
	while(pos < get_length())
	{
		int find_pos = find(str, pos);
		if(find_pos != npos)
		{
			if(pos != find_pos)
			{
				ret.push_back(sub_string(pos, find_pos));
			}
			pos = find_pos + str.get_length();
		}
		else
		{
			ret.push_back(sub_string(pos, get_length()));
			break;
		}
	}
	return ret;
}
std::vector<MyString> MyString::split2(const MyString &str)const
{
	std::vector<MyString> ret;
	int pos = 0;
	while(pos < get_length())
	{
		int find_pos = find(str, pos);
		if(find_pos != npos)
		{
			if(pos != find_pos)
			{
				ret.push_back(sub_string(pos, find_pos));
			}
			ret.push_back(sub_string(find_pos, find_pos + str.get_length()));
			pos = find_pos + str.get_length();
		}
		else
		{
			ret.push_back(sub_string(pos, get_length()));
			break;
		}
	}
	return ret;
}

MyString MyString::sub_string(int start, int end)const
{
	int s = (start > 0)?start:0;
	s = (s < get_length())?s:get_length();

	int e = (end < get_length())?end:get_length();
	e = (e > 0)?e:0;
	if(e < s) e = s;
	return MyString(data.substr (s, e-s).c_str ());
}
MyString MyString::operator[](int index)const
{
	assert(index >=0 && index < get_length());
	return data[index];
}
MyString MyString::operator()(int s, int e)const
{
	return sub_string(s, e);
}
MyString MyString::operator+(const MyString &str)
{
	std::string ret=data + str.data ;
	return MyString(ret.c_str ());
}
char MyString::get_code()const
{
	assert(get_length() == 1);
	return data[0];
}

MyString::MyString(char c)
{
	char cc[2]={c, 0};
	data = std::string(cc);
}

const char *MyString::c_str ()const
{
	return data.c_str ();
}


MyStringList operator+(const MyStringList &a, const MyStringList &b)
{
	MyStringList sum = a;
	sum.insert(sum.end(), b.begin(), b.end());
	return sum;
}

bool MyString::operator==(const MyString &it)const
{
	return data == it.data ;
}

bool MyString::operator!=(const MyString &it)const
{
	return !(*this == it) ;
}

bool MyString::operator<(const MyString &it)const
{
	return data < it.data ;
}

MyString MyString::operator *(int times)
{
	MyString result="";
	for(int i=0; i<times; i++)
	{
		result = result + *this;
	}
	return result;
}

MyString MyString::lstrip ()
{
	MyString ret = *this;
	while(ret.get_length () > 0)
	{
		if(ret[0].is_space ())
		{
			ret = ret(1, ret.get_length ());
		}
		else
		{
			break;
		}
	}
	return ret;
}

MyString MyString::rstrip ()
{
	MyString ret = *this;
	while(ret.get_length () > 0)
	{
		if(ret[ret.get_length ()-1].is_space ())
		{
			ret = ret(0, ret.get_length ()-1);
		}
		else
		{
			break;
		}
	}
	return ret;
}

MyString MyString::strip ()
{
	return this->lstrip ().rstrip();
}