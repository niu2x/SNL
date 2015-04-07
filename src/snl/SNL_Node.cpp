#include "SNL_Node.h"

SNL_Node::SNL_Node()
{
	child[0] = child[1] = child[2] = 0;
	sibling = 0;
}
SNL_Node::~SNL_Node ()
{
	if(sibling)
	{
		delete sibling; 
	}
	if(child[0])
	{
		delete child[0];
	}
	if(child[1])
	{
		delete child[1];
	}
	if(child[2])
	{
		delete child[2];
	}
}