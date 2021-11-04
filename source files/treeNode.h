#pragma once
#include <iostream>
#include <fstream>


using namespace std;

class treeNode
{
private:
	int frequency;
	char ch;

	treeNode* leftChild; 
	treeNode* rightChild;

public:
	treeNode(char ch = 0, int frequency = 0);

	/*GETTERS*/
	const char getChar() const { return ch; }
	const int getFrequency() const { return frequency; }
	treeNode* getLeftChild() const { return leftChild; }
	treeNode* getRightChild() const { return rightChild; }

	/*SETTERS*/
	void setChar(char ch);
	void setFrequency(int num);
	void setLeftChild(treeNode* node);
	void setRightChild(treeNode* node);
	void setRightChild(char ch, int _frequency = 0);
	void setLeftChild(char ch, int _frequency = 0);

	void increaseFrequency(int toAdd);

	static treeNode* createNewNode(char ch, int frequency = 0);
	friend ostream& operator<<(ostream& os, const treeNode& t);
	bool isLeaf();

};