#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <map>
#include <algorithm>
#include <regex>

#include "BitStream.h"
#include "HuffmanNode.h"
#include "HuffmanTree.h"

using namespace std;

class UI {
public:
	//structors
	UI();
	virtual ~UI();

	//ui funcs
	void run();
	void outputOptions();
	void takeInput(int inp);

	//main funcs
	void askForFile();
	void compressAndWriteFile();
	void decompressFile(string fileName);

	//utility
	string getRealFileName();
private:
	string fileName;
	string fileContents;
	bool terminate;
	BitStream bitstream;
	string fileExt;


	vector<HuffmanNode*> nodes;
	HuffmanTree* tree;
};

