#include "Tree.h"

TreeNode::TreeNodeType  TreeNode::TNT_PROGRAM = "program";
TreeNode::TreeNodeType  TreeNode::TNT_PROGRAM_HEAD = "program head";
TreeNode::TreeNodeType  TreeNode::TNT_DECLARE_PART = "declare part";
TreeNode::TreeNodeType  TreeNode::TNT_ALL_TYPE_DEC = "all type dec";
TreeNode::TreeNodeType  TreeNode::TNT_ALL_VAR_DEC = "all var dec";
TreeNode::TreeNodeType  TreeNode::TNT_ALL_PROC_DEC = "all proc dec";
TreeNode::TreeNodeType  TreeNode::TNT_ID = "id";
TreeNode::TreeNodeType  TreeNode::TNT_VALUE = "value";
TreeNode::TreeNodeType  TreeNode::TNT_ALL_PARA_DEC = "all para dec";
TreeNode::TreeNodeType  TreeNode::TNT_ALL_STM = "all stm";
TreeNode::TreeNodeType  TreeNode::TNT_ASSIGN_STM = "assign";
TreeNode::TreeNodeType  TreeNode::TNT_CALL_STM = "call";
TreeNode::TreeNodeType  TreeNode::TNT_IF_STM = "if";
TreeNode::TreeNodeType  TreeNode::TNT_WHILE_STM = "while";
TreeNode::TreeNodeType  TreeNode::TNT_INPUT_STM = "input";
TreeNode::TreeNodeType  TreeNode::TNT_OUTPUT_STM = "output";
TreeNode::TreeNodeType  TreeNode::TNT_RETURN_STM = "return";
TreeNode::TreeNodeType  TreeNode::TNT_EXP = "exp";
TreeNode::TreeNodeType  TreeNode::TNT_CMP_EXP = "cmp exp";
TreeNode::TreeNodeType  TreeNode::TNT_OP = "op";
TreeNode::TreeNodeType  TreeNode::TNT_PROGRAM_BODY = "progrom body";
TreeNode::TreeNode(const TreeNode::TreeNodeType &type, const MyString &value):type(type), value(value)
{
}

TreeNode::~TreeNode ()
{
}

TreeNode::TreeNodeType TreeNode::get_type()const
{
	return type;
}
MyString TreeNode::get_value()const
{
	return value;
}
	
TreeNode::ChildrenIterator TreeNode::begin()const    //用于遍历孩子节点
{
	return children.begin();
}
TreeNode::ChildrenIterator TreeNode::end()const
{
	return children.end();
}
void TreeNode::add_child(const TreeNode &child)
{
	children.push_back(child);
}


TreeVisitor::TreeVisitor (const TreeNode &root):root(root)
{
}

void PreRootVisitor::run ()
{
	__run__(root);
}

void PreRootVisitor::__run__ (const TreeNode &node)
{
	process(node);
	TreeNode::ChildrenIterator it = node.begin ();
	while(it != node.end())
	{
		__run__(*it);
		it ++;
	}
}