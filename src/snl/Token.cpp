#include "Token.h"
#include <assert.h>

TokenType Token:: T_ERROR = "error";
TokenType Token::T_NEWLINE = "\n";
TokenType Token:: T_PROGRAM = "program";
TokenType Token:: T_TYPE = "type";
TokenType Token:: T_VAR = "var";
TokenType Token:: T_PROCEDURE = "procedure";
TokenType Token:: T_BEGIN = "begin";
TokenType Token:: T_END = "end";
TokenType Token:: T_ARRAY = "array";
TokenType Token:: T_OF = "of";
TokenType Token:: T_RECORD = "record";
TokenType Token:: T_IF = "if";
TokenType Token:: T_THEN = "then";
TokenType Token:: T_ELSE = "else";
TokenType Token:: T_FI = "fi";
TokenType Token:: T_WHILE = "while";
TokenType Token:: T_DO = "do";
TokenType Token:: T_ENDWH = "endwh";
TokenType Token:: T_READ = "read";
TokenType Token:: T_WRITE = "write";
TokenType Token:: T_RETURN = "return";
TokenType Token:: T_INTEGER = "integer";
TokenType Token:: T_CHAR = "char";

TokenType Token:: T_INTEGER_VALUE = "integer_value";
TokenType Token:: T_ID = "id";
TokenType Token:: T_CHAR_VALUE = "char_value";

TokenType Token:: T_ADD = "+";
TokenType Token:: T_SUB = "-";
TokenType Token:: T_MUL = "*";
TokenType Token:: T_DIV = "/";
TokenType Token:: T_L_XKH = "(";
TokenType Token:: T_R_XKH = ")";
TokenType Token:: T_DOT = ".";
TokenType Token:: T_L_FKH = "[";
TokenType Token:: T_R_FKH = "]";
TokenType Token:: T_SEMICOLON = ";";
TokenType Token:: T_COLON = ":";
TokenType Token:: T_COMMA = ",";
TokenType Token:: T_LT = "<";
TokenType Token:: T_EQ = "=";
TokenType Token:: T_ASSIGN = ":=";
TokenType Token:: T_RANGE = "..";

MyString Token::delimiter = " ";

Token::Token(TokenType type):type(type)
{
	value.intValue = 0;
	value.charValue = " ";
}
Token::Token(TokenType type, int intValue):type(type)
{
	value.intValue = intValue;
	value.charValue = " ";
}
Token::Token(TokenType type, const MyString &charValue):type(type)
{
	value.intValue = 0;
	value.charValue = charValue;
}
Token::Token(TokenType type, int intValue, const MyString &charValue):type(type)
{
	value.intValue = intValue;
	value.charValue = charValue;
}
Token::Token(TokenType type, int intValue, const MyString &charValue, int lineno):type(type), lineno(lineno)
{
	value.intValue = intValue;
	value.charValue = charValue;
}
Token Token::check (MyStringList &strlist)
{
	assert(strlist.size() != 0);

	MyString str = strlist[0];
	MyString str_after = " ";
	if(strlist.size() > 1)
	{
		str_after = strlist[1];
	}	
	MyString str_after_after  = " ";
	if(strlist.size() > 2)
	{
		str_after_after = strlist[2];
	}
	strlist.erase(strlist.begin());

	if(str == T_NEWLINE)		return Token(T_NEWLINE);
	if(str == T_PROGRAM)		return Token(T_PROGRAM);
	if(str == T_TYPE)			return Token(T_TYPE);
	if(str == T_VAR)			return Token(T_VAR);
	if(str == T_PROCEDURE)		return Token(T_PROCEDURE);
	if(str == T_BEGIN)			return Token(T_BEGIN);
	if(str == T_END)			return Token(T_END);
	if(str == T_ARRAY)			return Token(T_ARRAY);
	if(str == T_OF)				return Token(T_OF);
	if(str == T_RECORD)			return Token(T_RECORD);
	if(str == T_IF)				return Token(T_IF);
	if(str == T_THEN)			return Token(T_THEN);
	if(str == T_ELSE)			return Token(T_ELSE);
	if(str == T_FI)				return Token(T_FI);
	if(str == T_WHILE)			return Token(T_WHILE);
	if(str == T_DO)				return Token(T_DO);
	if(str == T_ENDWH)			return Token(T_ENDWH);
	if(str == T_READ)			return Token(T_READ);
	if(str == T_WRITE)			return Token(T_WRITE);
	if(str == T_RETURN)			return Token(T_RETURN);
	if(str == T_INTEGER)		return Token(T_INTEGER);
	if(str == T_CHAR)			return Token(T_CHAR);

	if(str == T_ADD)			return Token(T_ADD);
	if(str == T_SUB)			return Token(T_SUB);
	if(str == T_MUL)			return Token(T_MUL);
	if(str == T_DIV)			return Token(T_DIV);
	if(str == T_L_XKH)			return Token(T_L_XKH);
	if(str == T_R_XKH)			return Token(T_R_XKH);
	if(str == T_L_FKH)			return Token(T_L_FKH);
	if(str == T_SEMICOLON)		return Token(T_SEMICOLON);
	if(str == T_R_FKH)			return Token(T_R_FKH);
	if(str == T_COMMA)			return Token(T_COMMA);
	if(str == T_LT)				return Token(T_LT);
	if(str == T_EQ)				return Token(T_EQ);

	if(str.is_number ())
	{
		return Token(T_INTEGER_VALUE, atoi(str.c_str()));
	}

	if(str[0].is_alpha () && (str(1, str.get_length ()) == "" || str(1, str.get_length ()).is_alpha_or_number ()))
	{
		return Token(T_ID, str);
	}
	
	if(str == T_DOT)
	{
		if(str_after == T_DOT)
		{
			strlist.erase(strlist.begin());
			return Token(T_RANGE);
		}
		else
		{
			return Token(T_DOT);
		}
	}

	if(str == T_COLON)
	{
		if(str_after == T_EQ)
		{
			strlist.erase(strlist.begin());
			return Token(T_ASSIGN);
		}
		else
		{
			return Token(T_ERROR, str);
		}
	}

	if(str == "\'")
	{
		if(str_after_after == "\'" && str_after.get_length () == 1)
		{
			strlist.erase(strlist.begin());
			strlist.erase(strlist.begin());
			return Token(T_CHAR_VALUE, str_after);
		}
		else
		{
			return Token(T_ERROR, str);
		}
	}
	else
	{
		return Token(T_ERROR, str);
	}
}

Token& Token::operator=(const Token &it)
{
	if(this != &it)
	{
		lineno = it.lineno;
		type = it.type ;
		value.intValue = it.value .intValue ;
		value.charValue = it.value .charValue ;
	}
	return *this;
}
Token::Token(const Token &it):type(it.type), lineno(it.lineno)
{
	value.charValue = it.value .charValue ;
	value.intValue = it.value .intValue ;
}