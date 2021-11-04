#include <iostream>
#include <fstream>
#include "bsTree.h"
#include "minHeap.h"
#include "huffmanTree.h"

using namespace std;

const int MAX_SIZE = 128;

int main()
{
	char fileName[MAX_SIZE];
	cout << "file name: ";
	cin >> fileName;
	char Cexit;

	ifstream infile(fileName);

	if (!infile)
	{
		cout << "unable to open file";
		Cexit = getchar();
		cin.get();
		exit(1);
	}

	bsTree t(infile); // build the tree from the file
	infile.close();

	HuffmanTree hf(&t); // create an huffman from the tree
	cout << hf; 

	Cexit = getchar();
	cin.get();	
}