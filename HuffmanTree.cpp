#include "HuffmanTree.h"

HuffmanTree::HuffmanTree() { }
HuffmanTree::HuffmanTree(vector<char> dataString) {
	data = dataString;
	map<char, int> byteFreq;

	//Load bytes into map and count frequencies
	for (int i = 0; i < data.size(); i++)
		++byteFreq[data[i]];

	//Sort the frequencies

	typedef map<char, int>::iterator it_type;
	for (it_type iterator = byteFreq.begin(); iterator != byteFreq.end(); iterator++)
		items.push_back(make_pair(iterator->second, iterator->first));
	sort(items.begin(), items.end(), [](pair<int, char> i, pair<int, char> j) { return (i.first < j.first); });

	//Load into nodes list
	for (int i = 0; i < items.size(); i++)
		nodes.push_back(new HuffmanNode(items[i].first, items[i].second));


	//Construct the tree
	constructTree();
}
HuffmanTree::~HuffmanTree() {
	deleteTree(root);
	delete root;
}

void HuffmanTree::constructTree() {
	while (nodes.size() > 1) {
		HuffmanNode* cNode = new HuffmanNode(nodes[0], nodes[1]);
		nodes.erase(nodes.begin(), nodes.begin() + 2);
		insertBackIntoList(cNode);
	}
	root = nodes[0];
	constructTable(root, "");

	//for (int i = 0; i < huffmanTable.size(); i++)
	//	cout << "Data: " << huffmanTable[i].first << " Code: " << huffmanTable[i].second << endl;
}
void HuffmanTree::constructTable(HuffmanNode* root, string code) {
	//We reached a leaf, so add it to the huffman code table
	if (root->getLeft() == NULL) {
		huffmanTable.push_back(make_pair(root->getData(), code));
		return;
	}
	else {
		constructTable(root->getLeft(), code + "0");
		constructTable(root->getRight(), code + "1");
	}

}
void HuffmanTree::printFrequencies() {
	for (int i = 0; i < items.size(); i++)
		cout << items[i].second << ": " << items[i].first << endl;
}
string HuffmanTree::encodeData() {
	string encodedData;
	for (int i = 0; i < data.size(); i++)
		encodedData += getCode(data[i]);
	return encodedData;
}
void HuffmanTree::encodeTree(HuffmanNode* root) {
	/*if (root->getLeft() == NULL) {
		encodedTree += "1";
		encodedTree += root->getData();
	}
	else {
		encodedTree += "0";
		encodeTree(root->getLeft());
		encodeTree(root->getRight());
	}*/

	if (root->getLeft() != NULL) {
		encodeTree(root->getLeft());
		encodeTree(root->getRight());
	}
	else
		encodedTree += '1';
	encodedTree += root->getData();
}
string HuffmanTree::getEncodedTree() {
	return encodedTree;
}
void HuffmanTree::decodeTree(string tree) {
	vector<HuffmanNode*> nodes;

	for (unsigned int i = 0; i < tree.length(); i++) {
		if (tree[i] == '1') {
			i++;
			HuffmanNode* node = new HuffmanNode(tree[i]);
			nodes.push_back(node);
		}
		else {
			HuffmanNode* right = nodes.back();
			nodes.pop_back();
			HuffmanNode* left = nodes.back();
			nodes.pop_back();
			HuffmanNode* node = new HuffmanNode(left, right);
			nodes.push_back(node);
		}
	}
	root = nodes[0];

	/*if (tree[idx] == '1') {
		++idx;
		return new HuffmanNode(tree[idx]);
	}
	else {
		HuffmanNode* leftChild = decodeTree(tree, ++idx);
		HuffmanNode* rightChild = decodeTree(tree, ++idx);
		return new HuffmanNode(leftChild, rightChild);
	}*/


}
void HuffmanTree::setEncodedData(string encodedData) {
	this->encodedData = encodedData;
}
string HuffmanTree::getDecodedData() {
	return decodedData;
}
string HuffmanTree::decodeData(string encodedText) {
	string decodedData;
	HuffmanNode* currNode = root;

	for (unsigned int i = 0; i < encodedText.length(); i++) {
		if (encodedText[i] == '0') {
			currNode = currNode->getLeft();
			if (currNode->getLeft() == NULL) {
				decodedData.push_back(currNode->getData());
				currNode = root;
			}
		}
		else if (encodedText[i] == '1') {
			currNode = currNode->getRight();
			if (currNode->getLeft() == NULL) {
				decodedData.push_back(currNode->getData());
				currNode = root;
			}
		}

	}

	return decodedData;
}

//Utility funcs
void HuffmanTree::insertBackIntoList(HuffmanNode* newNode) {
	int idx = -1;
	for (int i = 0; i < nodes.size(); i++) {
		if (newNode->getFrequency() <= nodes[i]->getFrequency()) {
			idx = i;
			break;
		}
	}
	if (idx == -1)
		nodes.push_back(newNode);
	else
		nodes.insert(nodes.begin() + idx, newNode);
}
bool HuffmanTree::isLeaf(HuffmanNode* node) {
	return (node->getLeft() == NULL && node->getRight() == NULL);
}
string HuffmanTree::getCode(char dataPoint) {
	map<char, string>::iterator it;

	for (int i = 0; i < huffmanTable.size(); i++) {
		if (huffmanTable[i].first == dataPoint)
			return huffmanTable[i].second;
	}
}
void HuffmanTree::deleteTree(HuffmanNode* root) {
	if (isLeaf(root))
		delete root;
	else {
		deleteTree(root->getLeft());
		deleteTree(root->getRight());
	}
}
void HuffmanTree::setEncodedTree(string eTree) {
	string tree = eTree;
	this->encodedTree = tree;
}

//debug
void HuffmanTree::printTable() {
	for (int i = 0; i < huffmanTable.size(); i++)
		cout << huffmanTable[i].first << ": " << huffmanTable[i].second << ": " <<  getCode(huffmanTable[i].first) << endl;
}
void HuffmanTree::printTree(HuffmanNode* p, int indent) {
	if (p != NULL) {
		string pData;
		if (p->getData() == NULL)
			pData = "NULL";
		else
			pData = p->getData();
		cout << pData << "\n ";
		if (p->getLeft() != NULL) printTree(p->getLeft(), indent + 6);
		if (p->getRight() != NULL) printTree(p->getRight(), indent + 6);
		if (indent) {
			std::cout << std::setw(indent) << ' ';
		}
	}
}
HuffmanNode* HuffmanTree::getRoot() {
	return root;
}
void HuffmanTree::setRoot(HuffmanNode* root) {
	this->root = root;
}