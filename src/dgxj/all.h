#include "../snl/SNL_Node.h"

SNL_Node *Program(void);				//�ܳ������������
SNL_Node * ProgramHead(void);			//����ͷ���ִ����������
SNL_Node * DeclarePart(void);			//�����������ִ����������
SNL_Node * TypeDec(void);				//�������������������
SNL_Node * TypeDeclaration(void);		//���������е���������
SNL_Node * TypeDecList(void);			//���������е���������
SNL_Node * TypeDecMore(void);			//���������е���������
void TypeId(SNL_Node * t);				//�������������ͱ�ʶ�������������
void TypeDef(SNL_Node * t);				//�������ʹ����������
void BaseType(SNL_Node * t);			//�������ʹ����������
void StructureType(SNL_Node * t);		//�ṹ���ʹ����������
void ArrayType(SNL_Node * t);			//�������ʹ����������
void RecType(SNL_Node * t);				//��¼���ʹ����������
SNL_Node * FieldDecList(void);			//��¼�����е������������������
SNL_Node * FieldDecMore(void);			//��¼�����е����������������������
void IdList(SNL_Node * t);				//��¼�����б�ʶ���������������
void IdMore(SNL_Node * t);				//��¼��������������ʶ���������������
SNL_Node * VarDec(void);				//�������������������
SNL_Node * VarDeclaration(void);		//�����������ִ����������
SNL_Node * VarDecList(void);			//�����������ִ����������
SNL_Node * VarDecMore(void);			//�����������ִ����������
void VarIdList(SNL_Node * t);			//�����������ֱ��������ִ����������
void VarIdMore(SNL_Node * t);			//�����������ֱ��������ִ����������
SNL_Node * ProcDec(void);				//�������������ܵĴ����������
SNL_Node * ProcDeclaration(void);		//�����������־���Ĵ����������
void ParamList(SNL_Node * t);			//���������еĲ����������ֵĴ����������
SNL_Node * ParamDecList(void);			//�����������������ֵķ����������
SNL_Node * ParamMore(void);				//���������в��������������ֵĴ����������
SNL_Node * Param(void);					//���������в��������в������ֵķ����������
void FormList(SNL_Node * t);			//���������еĲ��������в��������ֵĴ����������
void FidMore(SNL_Node * t);				//���������еĲ��������в��������ֵĴ����������
SNL_Node * ProcDecPart(void);			//�����������ֵĴ����������
SNL_Node * ProcBody(void);				//�����岿�ִ����������
SNL_Node * ProgramBody(void);			//�������ⲿ�ִ����������
SNL_Node * StmList(void);				//������в��ִ����������
SNL_Node * StmMore(void);				//������䲿�ִ����������
SNL_Node * Stm(void);					//���ݹ鴦���������
SNL_Node * AssCall(void);				//��ֵ���͹��̵�����䲿�ֵĴ����������
SNL_Node * AssignmentRest(void);		//��ֵ��䴦���������
SNL_Node * ConditionalStm(void);		//������䴦���������
SNL_Node * LoopStm(void);				//ѭ����䴦���������
SNL_Node * InputStm(void);				//������䴦���������
SNL_Node * OutputStm(void);				//�����䴦���������
SNL_Node * ReturnStm(void);				//���̷�����䴦���������
SNL_Node * CallStmRest(void);			//���̵�����䴦���������
SNL_Node * ActParamList(void);			//ʵ�β��ִ����������
SNL_Node * ActParamMore(void);			//����ʵ�β��ִ����������
SNL_Node * Exp(void);					//���ʽ�ݹ鴦���������
SNL_Node * Simple_exp(void);			//�򵥱��ʽ�ݹ鴦���������
SNL_Node * Term(void);					//��ݹ鴦���������
SNL_Node * Factor(void);				//���ӵݹ鴦���������
SNL_Node * Variable(void);				//�����������
void VariMore(SNL_Node * t);			//�������ಿ�ִ������
SNL_Node * Fieldvar(void);				//����������������
void FieldvarMore(SNL_Node * t);		//������������ִ����������
SNL_Node *ProcMore();
SNL_Node *RelExp();

