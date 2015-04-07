#ifndef __Token__
#define __Token__

#include "../MyString/MyString.h"

typedef MyString TokenType;

typedef struct TokenValue
{
	int intValue;
	MyString charValue;
}TokenValue;

class Token
{
public:
	TokenType type;
	TokenValue value;
	int lineno;
	Token(TokenType, int);
	Token(TokenType, const MyString &);
	Token(TokenType);
	Token(TokenType, int, const MyString &);
	Token(TokenType, int, const MyString &, int);
	Token& operator=(const Token &); 
	Token(const Token &);


	static Token check(MyStringList &);

	static TokenType T_ERROR;
	static TokenType T_NEWLINE;
	static TokenType T_PROGRAM;
	static TokenType T_TYPE;
	static TokenType T_VAR;
	static TokenType T_PROCEDURE;
	static TokenType T_BEGIN;
	static TokenType T_END;
	static TokenType T_ARRAY;
	static TokenType T_OF;
	static TokenType T_RECORD;
	static TokenType T_IF;
	static TokenType T_THEN;
	static TokenType T_ELSE;
	static TokenType T_FI;
	static TokenType T_WHILE;
	static TokenType T_DO;
	static TokenType T_ENDWH;
	static TokenType T_READ;
	static TokenType T_WRITE;
	static TokenType T_RETURN;
	static TokenType T_INTEGER;
	static TokenType T_CHAR;

	static TokenType T_INTEGER_VALUE;
	static TokenType T_ID;
	static TokenType T_CHAR_VALUE;

	static TokenType T_ADD;
	static TokenType T_SUB;
	static TokenType T_MUL;
	static TokenType T_DIV;
	static TokenType T_L_XKH;
	static TokenType T_R_XKH;
	static TokenType T_DOT;
	static TokenType T_L_FKH;
	static TokenType T_R_FKH;
	static TokenType T_SEMICOLON;
	static TokenType T_COMMA;
	static TokenType T_COLON;
	static TokenType T_LT;
	static TokenType T_EQ;
	static TokenType T_ASSIGN;
	static TokenType T_RANGE;

	static MyString delimiter;
};
#endif