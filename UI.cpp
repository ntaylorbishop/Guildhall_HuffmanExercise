#include "UI.h"

//STRUCTORS
UI::UI() {
	terminate = false;
}
UI::~UI() {
	delete tree;
}

//main funcs
void UI::run() {
	cout << "Welcome to the Guildhall Huffman Exercise!" << endl;
	outputOptions();
	while (!terminate) {}
}
void UI::outputOptions() {
	int input;

	cout << endl << "Please choose an option (Type corresponding number and hit enter): " << endl;
	cout << "\t1. Compress File" << endl;
	cout << "\t2. Decompress File" << endl;
	cout << "\t3. End Program" << endl;

	while (!(cin >> input)) {
		cout << "Invalid command. Please try again: ";
		cin.clear();
	}
	takeInput(input);

}
void UI::takeInput(int inp) {
	if (inp == 1) { //Compress file
		askForFile();
		compressAndWriteFile();
		cout << "File compressed successfully." << endl;
		outputOptions();
	}
	else if (inp == 2) { //Decompress file
		string str;
		cout << endl << "Please input the filename to decompress (Must end in .huff, type 'q' to go back):";

		//Wait for input and take in entire line. cin tokenizes with whitespace
		string tmp;
		cin >> tmp;
		getline(cin, str);
		tmp += str;
		str = tmp;

		fileName = str;

		string realFileName = getRealFileName();
		fileExt = fileName.substr(realFileName.length());

		if (fileExt.substr(fileExt.length() - 4) == "Huff")
			decompressFile(fileName);
		else if (str == "q")
			outputOptions();
		else {
			cout << endl << "Not a valid Huffman file. (Must end in Huff)" << endl;
			takeInput(2);
		}
		outputOptions();
	}
	else if (inp == 3) //Quit
		terminate = true;
	else {
		cout << "Incorrect command given. Please try again";
		outputOptions();
	}
}

//main funcs
void UI::askForFile() {
	fstream file;

	cout << endl << "Please input the name of the file you would like to compress. Type 'q' to go back:" << endl;
	cin >> fileName;
	if (fileName == "q")
		outputOptions();
	else {
		file.open(fileName.c_str(), ios::binary | fstream::in);
		if (file.is_open()) {
			cout << endl << "Loading file...";

			//Set extension
			string realFileName = getRealFileName();
			fileExt = fileName.substr(realFileName.length());

			vector<char> data;
			map<char, int> byteFreq;

			//load File contents into a vector of chars
			streampos start = file.tellg();
			file.seekg(0, std::ios::end);
			streampos end = file.tellg();
			file.seekg(0, std::ios::beg);
			data.resize(static_cast<size_t>(end - start));
			file.read(&data[0], data.size());

			delete tree;
			tree = new HuffmanTree(data);

			cout << " File loaded successfully." << endl << endl;
			file.close();

			//Compress and write
			compressAndWriteFile();
		}
		else {
			cout << "File not found. Please try again" << endl;
			askForFile();
		}
	}

}
void UI::compressAndWriteFile() {
	ofstream file;

	file.open((getRealFileName() + fileExt + "Huff").c_str(), ios::binary);
	if (file.is_open()) {
		cout << "Compressing...";

		//Get the encoded data and encoded tree
		string compressedData = tree->encodeData();
		tree->encodeTree(tree->getRoot());
		string encodedTree = tree->getEncodedTree();

		string packedData = bitstream.encodeData(compressedData, encodedTree);

		cout << " Encoding finished!" << endl << endl;
		cout << "Writing to file...";

		file << packedData;
		file.close();
		cout << " Writing to file finished!" << endl << endl;
	}
	else
		cout << "Something went wrong." << endl;
	outputOptions();
}
void UI::decompressFile(string fileName) {
	fstream file;

	if (fileName == "q")
		outputOptions();
	else {
		file.open(fileName.c_str(), ios::binary | fstream::in);
		if (file.is_open()) {
			cout << endl << "Decompressing file..." << endl;
			/*string fileContents;

			//Read in the file contents
			file.seekg(0, ios::end);
			fileContents.reserve(file.tellg());
			file.seekg(0, ios::beg);

			fileContents.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());*/

			vector<char> data;
			streampos start = file.tellg();
			file.seekg(0, std::ios::end);
			streampos end = file.tellg();
			file.seekg(0, std::ios::beg);
			data.resize(static_cast<size_t>(end - start));
			file.read(&data[0], data.size());

			string fileContents;
			for (unsigned int i = 0; i < data.size(); i++) 
				fileContents.push_back(data[i]);


			bitstream.decodeData(fileContents); //Decode the data
			delete tree; //Flush tree so we can pull in the decoded one
			tree = new HuffmanTree();
			
			//Decode the tree
			string encodedTree = bitstream.getDecodedTree();
			int idx = 0;

			tree->setEncodedTree(encodedTree);
			tree->decodeTree(encodedTree);

			//Output the decompressed file
			string originalFile = tree->decodeData(bitstream.getBitCodeData());

			ofstream outputFile;
			string origfileExt = fileExt.substr(0, fileExt.length() - 4);
			outputFile.open((getRealFileName() + origfileExt).c_str(), ios::binary);
			if (outputFile.is_open()) {
				outputFile << originalFile;
				cout << "Decompression finished!" << endl;
				outputFile.close();
				outputOptions();
			}
			else //Sanity check
				cout << "Something went wrong opening the decompression file to write to." << endl;
		}
		else {
			cout << "File not found. Please try again" << endl;
			askForFile();
		}
	}
}

//utility
string UI::getRealFileName() {
	return fileName.substr(0, fileName.find('.', 0));
}