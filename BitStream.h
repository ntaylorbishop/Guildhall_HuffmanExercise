#pragma once
#include <bitset>
#include <string>
#include <stdint.h>
#include <iostream>

using namespace std;

class BitStream {
public:
	BitStream();

	string encodeData(string compressedData, string eTree);
	void decodeData(string packedData); //Spits out the size of the tree, the encoded tree, then the padded buffer size, then the compressed data

	string getBitCodeData();
	string getDecodedTree();
private:
	//For decoding the compression
	string bitCodeData;
	string decodedTree;

	uint8_t BUFFER_PADDING_SIZE; //The size of padding at the end of the file. EG if the compressed data is 51 bits, then the padding size will be 5 

	string decodeTree(string eTree);
};