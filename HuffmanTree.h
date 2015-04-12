#pragma once
#include <vector>
#include <bitset>
#include <iostream>
#include <map>
#include <algorithm>
#include <iomanip>

#include "HuffmanNode.h"

using namespace std;
class HuffmanTree {
public:
	HuffmanTree();
	HuffmanTree(vector<char> data);
	~HuffmanTree();

	void constructTree();
	void constructTable(HuffmanNode* root, string code);
	void printFrequencies();
	string encodeData();

	//Encoding
	void encodeTree(HuffmanNode* root);
	string getEncodedTree();

	//Decoding
	void decodeTree(string tree);
	void setEncodedData(string encodedData);
	string getDecodedData();
	string decodeData(string encodedText);

	//utility funcs
	void insertBackIntoList(HuffmanNode* newNode);
	bool isLeaf(HuffmanNode* node);
	string getCode(char dataPoint);
	void deleteTree(HuffmanNode* root);
	void setEncodedTree(string eTree);

	//debug
	void printTable();
	void printTree(HuffmanNode* p, int indent = 0);
	HuffmanNode* getRoot();
	void setRoot(HuffmanNode* root);

private:
	HuffmanNode* root;
	vector<char> data;
	vector<HuffmanNode*> nodes;
	vector<pair<int, char>> items;
	vector<pair<char, string>> huffmanTable;
	string encodedTree;

	//Decoding
	string encodedData;
	string decodedData;
};

