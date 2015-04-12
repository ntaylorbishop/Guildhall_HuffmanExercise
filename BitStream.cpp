#include "BitStream.h"

//Public
BitStream::BitStream() {

}

string BitStream::encodeData(string compressedData, string eTree) {
	string encodedTree;
	//Output will look like: Size of tree | Tree | Padding | Compressed Data | Padded bits

	//Take care of converting the entire tree to binary
	for (int i = 0; i < eTree.length(); i++) {
		//if (eTree[i] == '0' || eTree[i] == '1')
		//	encodedTree.push_back(eTree[i]);
		//else
			encodedTree.append(bitset<8>(eTree[i]).to_string());
	}
	//Get size of tree
	string treeSize = bitset<16>(encodedTree.length()).to_string();

	//Get padding
	float sizeOfOutput = treeSize.length() + encodedTree.length() + compressedData.length();
	int paddingStep = (float)(sizeOfOutput / 8);
	char padding = (paddingStep + 1) * 8 - sizeOfOutput;

	//clear compressedData of extra carriage returns
	for (int i = 0; i < compressedData.size(); i++) {
		if (compressedData[i] == '\n')
			compressedData.erase(compressedData.begin() + i);
	}

	//Pad output first
	string paddingString;
	for (int i = 0; i < (int)padding; i++)
		paddingString.push_back('0');
	string bitData = treeSize + encodedTree + bitset<8>(padding).to_string() + compressedData + paddingString;

	string data;
	for (unsigned int i = 0; i < bitData.length(); i += 8) {
		unsigned char binToChar = (char)bitset<8>(bitData.substr(i, 8)).to_ulong();
		data.push_back(binToChar);
	}

	return data;
}
void BitStream::decodeData(string packedData) {
	//Convert everything back to a binary string
	string fileContents = "";
	for (int i = 0; i < packedData.size(); i++)
		fileContents.append(bitset<8>(packedData[i]).to_string());

	//Reset data members
	bitCodeData.clear();
	decodedTree.clear();

	int treeSize = bitset<16>(fileContents.substr(0, 16)).to_ulong();
	decodedTree = decodeTree(fileContents.substr(16, treeSize));
	int padding = bitset<8>(fileContents.substr(16 + treeSize, 8)).to_ulong();
	string bitCodeDataWithPadding = fileContents.substr(16 + treeSize + 8);
	bitCodeData = bitCodeDataWithPadding.substr(0, bitCodeDataWithPadding.size() - padding);

}

string BitStream::getBitCodeData() {
	return bitCodeData;
}
string BitStream::getDecodedTree() {
	return decodedTree;
}

string BitStream::decodeTree(string eTree) {
	string decodedTree;

	int idx = 0;
	for (int i = 0; i < eTree.length() / 8; i++) {
		char binToChar = char(bitset<8>(eTree.substr(idx, 8)).to_ulong());
		idx += 8;
		decodedTree.push_back(binToChar);
	}

	return decodedTree;
}