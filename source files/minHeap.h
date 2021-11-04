#pragma once
#include "bsTree.h"

class minHeap
{
private:
	treeNode **heap; // tree nodes pointers array
	int maxSize;
	int heapSize;

public:
	minHeap(int max);
	minHeap(bsTree* tr);
	~minHeap();

	int getMaxsize() { return maxSize; }

	bool isEmpty();
	bool insert(treeNode *newNode); // if the heap is full returns false
	treeNode* deleteMin();
	void buildHeap(bsTree* tree); // using floyd
	void treeToHeap(treeNode* root, int* i);

private:
	void fixHeap(int root);

	static int Parent(int node)		{ return (node - 1) / 2; }
	static int Left(int node)	    { return (2 * node + 1); }
	static int Right(int node)		{ return (2 * node + 2); }

};
