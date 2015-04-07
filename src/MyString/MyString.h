#ifndef __MyString__
#define __MyString__

#include <string>
#include <vector>
class MyString
{
private:
	std::string data;
public:
	static int npos;
	MyString(char c);
	MyString(const char *data="");
	MyString(const MyString&);
	MyString& operator=(const MyString&);
	~MyString();
	int get_length()const;
	int count(const MyString &)const;
	bool end_with(const MyString &)const;
	bool start_with(const MyString &)const;
	int find(const MyString &, int pos = 0)const;
	int rfind(const MyString &, int pos = std::string::npos)const;
	bool is_number()const;
	bool is_alpha()const;
	bool is_space()const;
	bool is_alpha_or_number()const;
	MyString join(const std::vector<MyString> &)const;
	MyString replace(const MyString &oldStr, const MyString &newStr, int times = 0)const;
	std::vector<MyString> split(const MyString &)const;
	std::vector<MyString> split2(const MyString &)const;       //°üº¬¶¨½ç·û
	MyString sub_string(int start, int end)const;
	MyString operator[](int)const;
	MyString operator()(int, int)const;
	MyString operator+(const MyString &);
	MyString operator*(int times);
	MyString lstrip();
	MyString rstrip();
	MyString strip();
	char get_code()const;
	const char *c_str()const;
	bool operator==(const MyString &it)const;
	bool operator<(const MyString &it)const;
	bool operator!=(const MyString &it)const;
};

typedef std::vector<MyString> MyStringList;
MyStringList operator+(const MyStringList&, const MyStringList&);
#endif