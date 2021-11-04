#pragma once
#include "treeNode.h"
#include "minHeap.h"
#include "bsTree.h"

#define max(a,b) ((a)>(b)?(a):(b))

class HuffmanTree
{
private:

	treeNode* root;
	bool allocated; // if allocted by this tree 


public:
	HuffmanTree(bsTree* tr);
	HuffmanTree(treeNode* root,int allocated);
	~HuffmanTree();
	
	treeNode* Huffman(bsTree* tr);
	static int getDepth(treeNode* node);

	friend ostream& operator<<(ostream& os, const HuffmanTree& T);

private:
	ostream& printHuffman(ostream& os, int* arr, int top, int* bits) const;
	ostream& printCode(ostream& os, int* arr, int top) const; //prints the huffman code of the char
	ostream& printChar(ostream& os, char ch) const; // prints a char
	
	static void deleteHuffman(treeNode* root);
};

