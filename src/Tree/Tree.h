#ifndef __my_tree
#define __my_tree

#include "../MyString/MyString.h"
#include <vector>

class TreeNode
{
public:
	typedef std::vector<TreeNode> ChildNodeList;
	typedef MyString TreeNodeType;
	typedef ChildNodeList::const_iterator ChildrenIterator;
private:
	MyString type;
	MyString value;
	ChildNodeList children;
public:
	static TreeNodeType TNT_PROGRAM;
	static TreeNodeType TNT_PROGRAM_HEAD;
	static TreeNodeType TNT_DECLARE_PART;
	static TreeNodeType TNT_PROGRAM_BODY;
	static TreeNodeType TNT_ALL_TYPE_DEC;
	static TreeNodeType TNT_ALL_VAR_DEC;
	static TreeNodeType TNT_ALL_PROC_DEC;
	static TreeNodeType TNT_ONE_TYPE_DEC;
	static TreeNodeType TNT_ONE_VAR_DEC;
	static TreeNodeType TNT_ONE_PROC_DEC;
	static TreeNodeType TNT_TYPE;
	static TreeNodeType TNT_ID;
	static TreeNodeType TNT_VALUE;
	static TreeNodeType TNT_ALL_PARA_DEC;
	static TreeNodeType TNT_ALL_STM;
	static TreeNodeType TNT_ASSIGN_STM;
	static TreeNodeType TNT_CALL_STM;
	static TreeNodeType TNT_IF_STM;
	static TreeNodeType TNT_WHILE_STM;
	static TreeNodeType TNT_INPUT_STM;
	static TreeNodeType TNT_OUTPUT_STM;
	static TreeNodeType TNT_RETURN_STM;
	static TreeNodeType TNT_EXP;
	static TreeNodeType TNT_CMP_EXP;
	static TreeNodeType TNT_OP;

public:
	TreeNode(const TreeNodeType &type, const MyString &value = "");
	~TreeNode();
	
	TreeNodeType get_type()const;
	MyString get_value()const;
	
	ChildrenIterator begin()const;    //用于遍历孩子节点
	ChildrenIterator end()const;

	void add_child(const TreeNode &);
};

class TreeVisitor
{
protected:
	const TreeNode &root;
public:
	TreeVisitor(const TreeNode &);
	virtual ~TreeVisitor(){}
	virtual void run() = 0;
	virtual void process(const TreeNode &) = 0;
};

class PreRootVisitor:public TreeVisitor
{
	void __run__(const TreeNode &);
public:
	virtual ~PreRootVisitor(){}
	virtual void run();
};

#endif