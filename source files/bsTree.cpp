#include "bsTree.h"


bsTree::bsTree(istream& in) : root(nullptr) , allocated(true)
{
	buildTree(in);
}

bsTree::bsTree(treeNode* rt,int allocated)
{
	this->allocated = allocated;
	root = rt;
}

bsTree::~bsTree()
{
	if (allocated)
		deleteTree(root);

	else
		root = nullptr;
}

void bsTree::makeEmpty()
{
	root = nullptr;
}

bool bsTree::isEmpty() const
{
	if (root == nullptr)
		return true;

	else return false;

}
	
bool bsTree::insertNode(treeNode* newNode)
{
	treeNode* temp;
	treeNode* parent = nullptr;
	temp = find(newNode->getChar(),parent);

	if (temp) // if found add 1 to frequency
	{
		temp->increaseFrequency(1);
		return false;
	}

	// else not found:
	treeNode* cur = root;

	while (cur) // searching for the leaf position
	{
		parent = cur;
		if (newNode->getChar() < cur->getChar())
			cur = cur->getLeftChild();

		else
			cur = cur->getRightChild();
	}

	if (parent == nullptr)
		root = newNode;

	else if (newNode->getChar() < parent->getChar())
		parent->setLeftChild(newNode);
	
	else
		parent->setRightChild(newNode);

	return true;
}

treeNode* bsTree::deleteNode(char ch)
{
	treeNode* parent=nullptr;
	treeNode* cur = root;

	cur = find(cur->getChar(), parent);

	if (cur == nullptr || root == nullptr ) // base case - not found
		return nullptr;

	
	// Case 1: the node has at most 1 child
	if (cur->getLeftChild() == nullptr || cur->getRightChild() == nullptr)
	{
		treeNode* toDelete = new treeNode(*cur); //save the node to return
		treeNode* child;

		if (cur->getLeftChild()) 	// if the child has no children, child will utilize with nullptr
			child = cur->getLeftChild();
		else
			child = cur->getRightChild();

		
		if (cur != root)
		{
			parent = cur;
			if (cur == parent->getLeftChild())
				parent->setLeftChild(child);
			else
				parent->setRightChild(child);
		}

		else
			root = child;

		return toDelete;
	}

	// Case 2: the node has 2 children
	else if (cur->getLeftChild() && cur->getRightChild())
	{
		bsTree subTree(cur->getRightChild(),false); //****maybe fail?**** take the minimum of the greater side
		treeNode* successor = subTree.getMin();
		
		nodeSwap(cur, successor); 

		return deleteNode(successor->getChar()); // recursivly delete the remain node (back to case 1)
	}
}

treeNode* bsTree::find(char ch, treeNode* parent) const
{
	treeNode* cur = root;
	parent = nullptr;

	while (cur) 
	{
		if (cur->getChar() == ch)
			return cur;

		else if (ch < cur->getChar()) // key smaller - go left
		{
			parent = cur;
			cur = cur->getLeftChild();
		}
		else						// key greater - go right
		{
			parent = cur;
			cur = cur->getRightChild();
		}	
	}
	parent = nullptr;
	return nullptr; // has not found
}

int bsTree::treeSize() const
{
	if (root == nullptr)
		return 0;

	bsTree leftSubtree(root->getLeftChild(),false);
	bsTree rightSubtree(root->getRightChild(),false);


	return leftSubtree.treeSize() + rightSubtree.treeSize() + 1;
}

treeNode* bsTree::getMin() const
{
	treeNode* cur = root;

	while (cur->getLeftChild() != nullptr)
		cur = cur->getLeftChild();

	return cur;
}

bsTree bsTree::getLeftSubTree() const
{
	bsTree leftSubtree(root->getLeftChild(),false);
	return leftSubtree;
}
bsTree bsTree::getRightSubTree() const
{
	bsTree rightSubtree(root->getRightChild(),false);
	return rightSubtree;
}

void bsTree::nodeSwap(treeNode* cur, treeNode* successor)
{
	treeNode temp;
	temp.setChar(cur->getChar());
	temp.setFrequency(cur->getFrequency());
	
	cur->setChar(successor->getChar());
	cur->setFrequency(successor->getFrequency());

	successor->setChar(temp.getChar());
	successor->setFrequency(temp.getFrequency());
}

void bsTree::buildTree(istream& in)
{
	char ch;
	treeNode* node;

	while (!in.eof())
	{
		in.get(ch);
		if (in.eof()) break; // prevent overreading
		node = treeNode::createNewNode(ch,1);
		
		if (!insertNode(node)) // if the item is already existed - delete it
			delete[] node;
	}
}


void bsTree::deleteTree(treeNode* root)
{
	if (root == nullptr)
		return;

	deleteTree(root->getLeftChild());
	deleteTree(root->getRightChild());

	delete[]root;
}


