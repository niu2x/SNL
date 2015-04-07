#include "table.h"
#include <map>

std::map<TokenType, int> table[100];
void init_table()
{
	table[NT_Program][Token::T_PROGRAM] = 1;

	table[NT_ProgramHead][Token::T_PROGRAM] = 2;

	table[NT_ProgramName][Token::T_ID] = 3;

	table[NT_DeclarePart][Token::T_TYPE] = 4;
	table[NT_DeclarePart][Token::T_VAR] = 4;
	table[NT_DeclarePart][Token::T_PROCEDURE] = 4;
	table[NT_DeclarePart][Token::T_BEGIN] = 4;

	table[NT_TypeDecpart][Token::T_VAR ] = 5;
	table[NT_TypeDecpart][Token::T_PROCEDURE ] = 5;
	table[NT_TypeDecpart][Token::T_BEGIN ] = 5;
	table[NT_TypeDecpart][Token::T_TYPE ] = 6;

	table[NT_TypeDec][Token::T_TYPE] = 7;

	table[NT_TypeDecList][Token::T_ID] = 8;

	table[NT_TypeDecMore][Token::T_VAR] = 9;
	table[NT_TypeDecMore][Token::T_PROCEDURE] = 9;
	table[NT_TypeDecMore][Token::T_BEGIN] = 9;
	table[NT_TypeDecMore][Token::T_ID] = 10;

	table[NT_TypeId][Token::T_ID] = 11;

	table[NT_TypeDef][Token::T_INTEGER] = 12;
	table[NT_TypeDef][Token::T_CHAR] = 12;
	table[NT_TypeDef][Token::T_ARRAY] = 13;
	table[NT_TypeDef][Token::T_RECORD] = 13;
	table[NT_TypeDef][Token::T_ID] = 14;


	table[NT_BaseType][Token::T_INTEGER] = 15;
	table[NT_BaseType][Token::T_CHAR] = 16;
	
	table[NT_StructureType][Token::T_ARRAY] = 17;
	table[NT_StructureType][Token::T_RECORD] = 18;

	table[NT_ArrayType][Token::T_ARRAY] = 19;

	table[NT_Low][Token::T_INTEGER_VALUE] = 20;

	table[NT_Up][Token::T_INTEGER_VALUE] = 21;
	
	table[NT_RecordType][Token::T_RECORD] = 22;

	table[NT_FieldDecList][Token::T_INTEGER] = 23;
	table[NT_FieldDecList][Token::T_CHAR] = 23;
	table[NT_FieldDecList][Token::T_ARRAY] = 24;

	table[NT_FieldDecMore][Token::T_END] = 25;
	table[NT_FieldDecMore][Token::T_INTEGER] = 26;
	table[NT_FieldDecMore][Token::T_CHAR] = 26;
	table[NT_FieldDecMore][Token::T_ARRAY] = 26;

	table[NT_IdList][Token::T_ID] = 27;
	
	table[NT_IdMore][Token::T_SEMICOLON] = 28;
	table[NT_IdMore][Token::T_COMMA] = 29;

	table[NT_VarDecpart][Token::T_PROCEDURE] = 30;
	table[NT_VarDecpart][Token::T_BEGIN] = 30;
	table[NT_VarDecpart][Token::T_VAR] = 31;
	
	table[NT_VarDec][Token::T_VAR] = 32;

	table[NT_VarDecList][Token::T_INTEGER] = 33;
	table[NT_VarDecList][Token::T_CHAR] = 33;
	table[NT_VarDecList][Token::T_ARRAY] = 33;
	table[NT_VarDecList][Token::T_RECORD] = 33;
	table[NT_VarDecList][Token::T_ID] = 33;

	table[NT_VarDecMore][Token::T_PROCEDURE] = 34;
	table[NT_VarDecMore][Token::T_BEGIN] = 34;
	table[NT_VarDecMore][Token::T_INTEGER] = 35;
	table[NT_VarDecMore][Token::T_CHAR] = 35;
	table[NT_VarDecMore][Token::T_ARRAY] = 35;
	table[NT_VarDecMore][Token::T_RECORD] = 35;
	table[NT_VarDecMore][Token::T_ID] = 35;

	table[NT_VarIdList][Token::T_ID] = 36;

	table[NT_VarIdMore][Token::T_SEMICOLON] = 37;
	table[NT_VarIdMore][Token::T_COMMA] = 38;

	table[NT_ProcDecpart][Token::T_BEGIN] = 39;
	table[NT_ProcDecpart][Token::T_PROCEDURE] = 40;

	table[NT_ProcDec][Token::T_PROCEDURE] = 41;
	
	table[NT_ProcDecMore][Token::T_BEGIN] = 42;
	table[NT_ProcDecMore][Token::T_PROCEDURE] = 43;

	table[NT_ProcName][Token::T_ID] = 44;

	table[NT_ParamList][Token::T_R_XKH] = 45;
	table[NT_ParamList][Token::T_INTEGER] = 46;
	table[NT_ParamList][Token::T_CHAR] = 46;
	table[NT_ParamList][Token::T_ARRAY] = 46;
	table[NT_ParamList][Token::T_RECORD] = 46;
	table[NT_ParamList][Token::T_ID] = 46;
	table[NT_ParamList][Token::T_VAR] = 46;

	table[NT_ParamDecList][Token::T_INTEGER] = 47;
	table[NT_ParamDecList][Token::T_CHAR] = 47;
	table[NT_ParamDecList][Token::T_ARRAY] = 47;
	table[NT_ParamDecList][Token::T_RECORD] = 47;
	table[NT_ParamDecList][Token::T_ID] = 47;
	table[NT_ParamDecList][Token::T_VAR] = 47;

	table[NT_ParamMore][Token::T_R_XKH] = 48;
	table[NT_ParamMore][Token::T_SEMICOLON] = 49;

	table[NT_Param][Token::T_INTEGER] = 50;	
	table[NT_Param][Token::T_CHAR] = 50;
	table[NT_Param][Token::T_ARRAY] = 50;
	table[NT_Param][Token::T_RECORD] = 50;
	table[NT_Param][Token::T_ID] = 50;
	table[NT_Param][Token::T_VAR] = 51;

	table[NT_FormList][Token::T_ID] = 52;

	table[NT_FidMore][Token::T_SEMICOLON] = 53;
	table[NT_FidMore][Token::T_COMMA] = 53;
	table[NT_FidMore][Token::T_R_XKH] = 53;
	table[NT_FidMore][Token::T_COMMA] = 54;

	table[NT_ProcDecPart][Token::T_TYPE] = 55;
	table[NT_ProcDecPart][Token::T_VAR] = 55;
	table[NT_ProcDecPart][Token::T_BEGIN] = 55;
	table[NT_ProcDecPart][Token::T_PROCEDURE] = 55;

	table[NT_ProcBody][Token::T_BEGIN] = 56;

	table[NT_ProgramBody][Token::T_BEGIN] = 57;

	table[NT_StmList][Token::T_ID] = 58;
	table[NT_StmList][Token::T_IF] = 58;
	table[NT_StmList][Token::T_WHILE] = 58;
	table[NT_StmList][Token::T_RETURN] = 58;
	table[NT_StmList][Token::T_READ] = 58;
	table[NT_StmList][Token::T_WRITE] = 58;

	table[NT_StmMore][Token::T_ELSE] = 59;
	table[NT_StmMore][Token::T_FI] = 59;
	table[NT_StmMore][Token::T_END] = 59;
	table[NT_StmMore][Token::T_ENDWH] = 59;
	table[NT_StmMore][Token::T_SEMICOLON] = 60;

	table[NT_Stm][Token::T_IF] = 61;
	table[NT_Stm][Token::T_WHILE] = 62;
	table[NT_Stm][Token::T_READ] = 63;
	table[NT_Stm][Token::T_WRITE] = 64;
	table[NT_Stm][Token::T_RETURN] = 65;
	table[NT_Stm][Token::T_ID] = 66;

	table[NT_AssCall][Token::T_ASSIGN] = 67;
	table[NT_AssCall][Token::T_L_FKH] = 67;
	table[NT_AssCall][Token::T_DOT] = 67;
	table[NT_AssCall][Token::T_L_XKH] = 68;

	table[NT_AssignmentRest][Token::T_L_FKH] = 69;
	table[NT_AssignmentRest][Token::T_DOT] = 69;
	table[NT_AssignmentRest][Token::T_ASSIGN] = 69;

	table[NT_ConditionalStm][Token::T_IF] = 70;
	
	table[NT_LoopStm][Token::T_WHILE] = 71;
	
	table[NT_InputStm][Token::T_READ] = 72;
	
	table[NT_Invar][Token::T_ID] = 73;

	table[NT_OutputStm][Token::T_WRITE] = 74;
	
	table[NT_ReturnStm][Token::T_RETURN] = 75;

	table[NT_CallStmRest][Token::T_L_XKH] = 76;

	table[NT_ActParamList][Token::T_R_XKH] = 77;
	table[NT_ActParamList][Token::T_L_XKH] = 78;
	table[NT_ActParamList][Token::T_ID] = 78;
	table[NT_ActParamList][Token::T_INTEGER_VALUE] = 78;

	table[NT_ActParamMore][Token::T_R_XKH] = 79;
	table[NT_ActParamMore][Token::T_COMMA] = 80;

	table[NT_RelExp][Token::T_L_XKH] = 81;
	table[NT_RelExp][Token::T_ID] = 81;
	table[NT_RelExp][Token::T_INTEGER_VALUE] = 81;

	table[NT_OtherRelE][Token::T_LT] = 82;
	table[NT_OtherRelE][Token::T_EQ] = 82;

	table[NT_Exp][Token::T_L_XKH] = 83;
	table[NT_Exp][Token::T_ID] = 83;
	table[NT_Exp][Token::T_INTEGER_VALUE] = 83;

	table[NT_OtherTerm][Token::T_LT] = 84;
	table[NT_OtherTerm][Token::T_EQ] = 84;
	table[NT_OtherTerm][Token::T_R_FKH] = 84;
	table[NT_OtherTerm][Token::T_THEN] = 84;
	table[NT_OtherTerm][Token::T_ELSE] = 84;
	table[NT_OtherTerm][Token::T_FI] = 84;
	table[NT_OtherTerm][Token::T_DO] = 84;
	table[NT_OtherTerm][Token::T_ENDWH] = 84;
	table[NT_OtherTerm][Token::T_R_XKH] = 84;
	table[NT_OtherTerm][Token::T_END] = 84;
	table[NT_OtherTerm][Token::T_SEMICOLON] = 84;
	table[NT_OtherTerm][Token::T_COMMA] = 84;

	table[NT_OtherTerm][Token::T_ADD] = 85;
	table[NT_OtherTerm][Token::T_SUB] = 85;

	table[NT_Term][Token::T_L_XKH] = 86;
	table[NT_Term][Token::T_INTEGER_VALUE] = 86;
	table[NT_Term][Token::T_ID] = 86;

	table[NT_OtherFactor][Token::T_ADD] = 87;
	table[NT_OtherFactor][Token::T_SUB] = 87;
	table[NT_OtherFactor][Token::T_LT] = 87;
	table[NT_OtherFactor][Token::T_EQ] = 87;
	table[NT_OtherFactor][Token::T_R_FKH] = 87;
	table[NT_OtherFactor][Token::T_THEN] = 87;
	table[NT_OtherFactor][Token::T_ELSE] = 87;
	table[NT_OtherFactor][Token::T_FI] = 87;
	table[NT_OtherFactor][Token::T_DO] = 87;
	table[NT_OtherFactor][Token::T_ENDWH] = 87;
	table[NT_OtherFactor][Token::T_R_XKH] = 87;
	table[NT_OtherFactor][Token::T_END] = 87;
	table[NT_OtherFactor][Token::T_SEMICOLON ] = 87;
	table[NT_OtherFactor][Token::T_COMMA] = 87;

	table[NT_OtherFactor][Token::T_MUL] = 88;
	table[NT_OtherFactor][Token::T_DIV] = 88;

	table[NT_Factor][Token::T_L_XKH] = 89;
	table[NT_Factor][Token::T_INTEGER_VALUE] = 90;
	table[NT_Factor][Token::T_ID] = 91;

	table[NT_Variable][Token::T_ID] = 92;

	table[NT_VariMore][Token::T_ASSIGN] = 93;
	table[NT_VariMore][Token::T_MUL] = 93;
	table[NT_VariMore][Token::T_DIV] = 93;
	table[NT_VariMore][Token::T_ADD] = 93;
	table[NT_VariMore][Token::T_SUB] = 93;
	table[NT_VariMore][Token::T_LT] = 93;
	table[NT_VariMore][Token::T_EQ] = 93;
	table[NT_VariMore][Token::T_THEN] = 93;
	table[NT_VariMore][Token::T_ELSE] = 93;
	table[NT_VariMore][Token::T_FI] = 93;
	table[NT_VariMore][Token::T_R_FKH] = 93;
	table[NT_VariMore][Token::T_DO] = 93;
	table[NT_VariMore][Token::T_ENDWH] = 93;
	table[NT_VariMore][Token::T_R_XKH] = 93;
	table[NT_VariMore][Token::T_END] = 93;
	table[NT_VariMore][Token::T_SEMICOLON] = 93;
	table[NT_VariMore][Token::T_COMMA] = 93;
	table[NT_VariMore][Token::T_L_FKH] = 94;
	table[NT_VariMore][Token::T_DOT] = 95;

	table[NT_FieldVar][Token::T_ID] = 96;

	table[NT_FieldVarMore][Token::T_ASSIGN] = 97;
	table[NT_FieldVarMore][Token::T_MUL] = 97;
	table[NT_FieldVarMore][Token::T_DIV] = 97;
	table[NT_FieldVarMore][Token::T_ADD] = 97;
	table[NT_FieldVarMore][Token::T_SUB] = 97;
	table[NT_FieldVarMore][Token::T_LT] = 97;
	table[NT_FieldVarMore][Token::T_EQ] = 97;
	table[NT_FieldVarMore][Token::T_THEN] = 97;
	table[NT_FieldVarMore][Token::T_ELSE] = 97;
	table[NT_FieldVarMore][Token::T_FI] = 97;
	table[NT_FieldVarMore][Token::T_DO] = 97;
	table[NT_FieldVarMore][Token::T_ENDWH] = 97;
	table[NT_FieldVarMore][Token::T_R_XKH] = 97;
	table[NT_FieldVarMore][Token::T_END] = 97;
	table[NT_FieldVarMore][Token::T_SEMICOLON] = 97;
	table[NT_FieldVarMore][Token::T_COMMA] = 97;
	table[NT_FieldVarMore][Token::T_L_FKH] = 98;

	table[NT_CmpOp][Token::T_LT] = 99;
	table[NT_CmpOp][Token::T_EQ] = 100;

	table[NT_AddOp][Token::T_ADD] = 101;
	table[NT_AddOp][Token::T_SUB] = 102;

	table[NT_MultOp][Token::T_MUL] = 103;
	table[NT_MultOp][Token::T_DIV] = 104;
}
