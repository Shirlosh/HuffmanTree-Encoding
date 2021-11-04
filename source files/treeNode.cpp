#include "TreeNode.h"

treeNode::treeNode(char ch, int frequency) : frequency(frequency), ch(ch)
{
	leftChild = nullptr;
	rightChild = nullptr;
}

void treeNode::setChar(char ch)
{
	this->ch = ch;
}

void treeNode::setFrequency(int num)
{
	this->frequency = num;
}

void treeNode::setLeftChild(treeNode* node)
{
	leftChild = node;
}

void treeNode::setRightChild(treeNode* node) 
{
	rightChild = node;
}


void treeNode::setLeftChild(char ch, int _frequency)
{
	leftChild->ch = ch;
	leftChild->frequency = _frequency;
}

void treeNode::setRightChild(char ch, int _frequency)
{
	rightChild->ch = ch;
	rightChild->frequency = _frequency;
}


void treeNode::increaseFrequency(int toAdd)
{
	frequency += toAdd;
}

treeNode* treeNode::createNewNode(char ch, int frequency) 
{
	treeNode* newNode = new treeNode(ch, frequency);
	
	return newNode;
}

bool treeNode::isLeaf()
{
	// if the node has at least one child:
	if(leftChild || rightChild)
		return false;
	// the node has no child - is leaf
	else
		return true;
}

ostream& operator<<(ostream& os, const treeNode& t)
{
	os << "the char: " << t.ch << " and its frequency: " << t.frequency;

	return os;
}
