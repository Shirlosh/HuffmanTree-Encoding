#include "huffmanTree.h"

HuffmanTree::HuffmanTree(bsTree* tr) : root(nullptr)
{
	root = Huffman(tr);
}

HuffmanTree::HuffmanTree(treeNode* root,int allocated)
{
    this->root = root;
    this->allocated = allocated;
}

HuffmanTree::~HuffmanTree()
{
    if (allocated)
        deleteHuffman(root);

    else
        root = nullptr;
}

treeNode* HuffmanTree::Huffman(bsTree* tr)
{
	minHeap h(tr);
	int n = h.getMaxsize();

	for (int i = 0; i < n-1; i++)
	{
		treeNode* node = new treeNode;

		node->setLeftChild(h.deleteMin());
		node->setRightChild(h.deleteMin());

		node->setFrequency(node->getLeftChild()->getFrequency() + node->getRightChild()->getFrequency());
		node->setChar(0);
		h.insert(node);
	}
	return h.deleteMin();
}

int HuffmanTree::getDepth(treeNode* node)
{
    if (!node)
        return 0;
    int lDepth = getDepth(node->getLeftChild());
    int rDepth = getDepth(node->getRightChild());

    return max(lDepth, rDepth) + 1 ;
}

ostream& HuffmanTree::printHuffman(ostream& os,int *arr,int top,int *bits) const
{
    // If this is a leaf node, then print the char and its code 
    if (root->isLeaf())
    {
        if (top == 0) top = 1; // if the tree has only root
        printChar(os, root->getChar());
        printCode(os, arr, top);
        *bits += root->getFrequency() * (top);
    }

    else
    {
        // Assign 0 to left edge
        if (root->getLeftChild())
        {
            arr[top] = 0;
            HuffmanTree leftsubtree(root->getLeftChild(), false);
            leftsubtree.printHuffman(os, arr, top + 1, bits);
        }

        // Assign 1 to right edge
        if (root->getRightChild())
        {
            arr[top] = 1;
            HuffmanTree rightsubtree(root->getRightChild(), false);
            rightsubtree.printHuffman(os, arr, top + 1, bits);
        }

    }
    
    return os;
}

ostream& HuffmanTree::printCode(ostream& os, int* arr, int top) const
{
     for (int i = 0; i < top; i++)
        os << arr[i];
  
    os << endl;

    return os;
}

ostream& HuffmanTree::printChar(ostream& os, char ch) const
{
    if (ch == '\n')
        os << "'" << "\\n" << "' - ";

    else if (ch == '\t')
        os << "'" << "\\t" << "' - ";

    else
        os << "'" << ch << "' - ";

    return os;
}

void HuffmanTree::deleteHuffman(treeNode* root)
{
    if (root == nullptr)
        return;

    deleteHuffman(root->getLeftChild());
    deleteHuffman(root->getRightChild());

    delete[]root;
}

ostream& operator<<(ostream& os, const HuffmanTree& T)
{
    int size = HuffmanTree::getDepth(T.root);
    int bits = 0;
    int *arr = new int[size]; // huffman code amount of digits is at least equal to the tree depth
    arr[0] = 1; // utilizing the first place with 1 for the case the tree has only root (no childs)
   
    T.printHuffman(os,arr,0,&bits);
    delete[] arr;

    os << "Encoded file weight: " << bits << " bits" << endl;

    return os;
}
