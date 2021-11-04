#pragma once
#include "treeNode.h"

using namespace std;

class bsTree
{
private:
	treeNode *root;
	bool allocated; // if allocted by this tree 

public:
	bsTree(istream& in);
	bsTree(treeNode *rt,int allocated);
	~bsTree();		    // if allocated - delete the nodes.

	/*GETTERS*/
	treeNode* getRoot() const { return root; }
	treeNode* getMin() const;
	bsTree getLeftSubTree() const;
	bsTree getRightSubTree() const;
	int treeSize() const;

private:
	/*TREE FUNCS*/
	void makeEmpty();
	bool isEmpty() const;
	bool insertNode(treeNode* node);					// returns false if the item is already existed else - true
	treeNode* deleteNode(char ch);						// returns false if the node couldn't be found
	treeNode* find(char ch, treeNode* parent) const;    // returns the requested node - if doesnt exist returns false
	void buildTree(istream& in);					  	//returns treeNode array sorted by ascii values

	static void deleteTree(treeNode* root);
	static void nodeSwap(treeNode* cur,treeNode* successor); // swap ONLY nodes frequency and char (WITHOUT CHILDS!)
};

