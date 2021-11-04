#include "minHeap.h"

minHeap::minHeap(int max)
{
	maxSize = max;
	heap = new treeNode*[maxSize];
	heapSize = 0;
}

minHeap::minHeap(bsTree *tr)
{
	heapSize = maxSize = tr->treeSize();
	heap = new treeNode*[maxSize];
	buildHeap(tr);
}

minHeap::~minHeap() 
{ 
	for (int i = 0; i < heapSize; i++)
		delete[] heap[i];
	delete[] heap;
}

bool minHeap::isEmpty()
{
	if (heap == nullptr)
		return true;

	else return false;
}

bool minHeap::insert(treeNode* newNode)
{
	if (heapSize == maxSize)
		return false;

	int i = heapSize;
	heapSize++;

	while ((i > 0) && newNode->getFrequency() < heap[Parent(i)]->getFrequency())
	{
		heap[i] = heap[Parent(i)];
		i = Parent(i);
	}
	heap[i] = newNode;
	return true;
}

treeNode* minHeap::deleteMin()
{
	if (heapSize == 0)
		return nullptr;

	treeNode *min = heap[0];
	heapSize--;
	heap[0] = heap[heapSize];
	heap[heapSize] = nullptr;

	fixHeap(0);
	return min;
}

void minHeap::treeToHeap(treeNode* root, int* i)
{
	if (root == nullptr)
		return;

	heap[(*i)++] = treeNode::createNewNode(root->getChar(), root->getFrequency());
	treeToHeap(root->getLeftChild(), i);
	treeToHeap(root->getRightChild(), i);
}

void minHeap::buildHeap(bsTree *tree)
{
	int i = 0;
	treeToHeap(tree->getRoot(), &i); // utilize heap with a sorted preorder(by char) array 
	
	for (i = heapSize / 2 - 1; i >= 0; i--) // floyd fix to minHeap
		fixHeap(i);
}

void minHeap::fixHeap(int root) 
{
	int min;
	int left = Left(root);
	int right = Right(root);

	//find min among root,left,right
	if (left < heapSize && heap[left]->getFrequency() < heap[root]->getFrequency())
		min = left;

	else min = root;

	if (right<heapSize && heap[right]->getFrequency() < heap[min]->getFrequency())
		min = right;

	if(min!=root)
	{
		swap(heap[root], heap[min]);
		fixHeap(min);
	}
}
