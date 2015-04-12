#include "HuffmanNode.h"

HuffmanNode::HuffmanNode() {
	frequency = 0;
	data = '0';
	left = right = NULL;
}
HuffmanNode::HuffmanNode(char data) {
	this->frequency = 0;
	this->data = data;
	left = right = NULL;
}
HuffmanNode::HuffmanNode(int frequency, char data) {
	this->frequency = frequency;
	this->data = data;
	left = right = NULL;
}
HuffmanNode::HuffmanNode(HuffmanNode* left, HuffmanNode* right) {
	this->frequency = left->getFrequency() + right->getFrequency();
	this->data = '0';
	this->left = left;
	this->right = right;
}
HuffmanNode::~HuffmanNode() {

}


void HuffmanNode::addLeftNode(HuffmanNode* left) {
	this->left = left;
}
void HuffmanNode::addRightNode(HuffmanNode* right) {
	this->right = right;
}
HuffmanNode* HuffmanNode::getLeft() {
	return left;
}
HuffmanNode* HuffmanNode::getRight() {
	return right;
}

int HuffmanNode::getFrequency() {
	return frequency;
}
char HuffmanNode::getData() {
	return data;
}
void HuffmanNode::setFrequency(int freq) {
	this->frequency = freq;
}
void HuffmanNode::setData(char data) {
	this->data = data;
}