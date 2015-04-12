#pragma once
#include <cstdlib>

class HuffmanNode
{
public:
	HuffmanNode();
	HuffmanNode(char data);
	HuffmanNode(int frequency, char data);
	HuffmanNode(HuffmanNode* left, HuffmanNode* right);
	~HuffmanNode();

	void addLeftNode(HuffmanNode* left);
	void addRightNode(HuffmanNode* right);
	HuffmanNode* getLeft();
	HuffmanNode* getRight();

	int getFrequency();
	char getData();
	void setFrequency(int freq);
	void setData(char data);
private:
	HuffmanNode* left;
	HuffmanNode* right;
	int frequency;
	char data;
};

