#include <queue>
#include <algorithm>
#include <cstring>
#include "bit_stream.h"
#include "huffman.h"

bool parseArguments(int argc, char **argv, std::string &inputFile, std::string &outputFile) {
	const int ARGUMENTS_NUMBER = 6;

	if (argc != ARGUMENTS_NUMBER) {
		throw HuffmanArchiver::ArchiverExeption("Wrong arguments number.");
	}

	std::size_t inputFilenamePosition = 0;
	std::size_t outputFilenamePosition = 0;

	for (std::size_t i = 1; i < ARGUMENTS_NUMBER - 1; i++) {
		if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
			inputFile = argv[i + 1];
			inputFilenamePosition = i + 1;
		}

		if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
			outputFile = argv[i + 1];
			outputFilenamePosition = i + 1;
		}
	}

	if (inputFilenamePosition == 0 || outputFilenamePosition == 0) {
		throw HuffmanArchiver::ArchiverExeption("Wrong arguments.");
	}

	bool isEncoding;
	bool isModeFlagFound = false;

	for (std::size_t i = 1; i < ARGUMENTS_NUMBER; i++) {
		if (i != inputFilenamePosition && i != outputFilenamePosition) {
			if (strcmp(argv[i], "-c") == 0) {
				isEncoding = true;
				isModeFlagFound = true;
				break;
			}

			if (strcmp(argv[i], "-u") == 0) {
				isEncoding = false;
				isModeFlagFound = true;
				break;
			}
		}
	}

	if (!isModeFlagFound) {
		throw HuffmanArchiver::ArchiverExeption("Mode flag not found.");
	}

	return isEncoding;
}

void openFile(std::fstream &stream, const std::string &filename, std::ios_base::openmode mode) {
	stream = std::fstream(filename, mode | std::ios_base::binary);

	if (stream.is_open() == false) {
		throw HuffmanArchiver::ArchiverExeption("Failed opening file.");
	}
}

void printStatistic(std::istream &inputFile, std::ostream &outputFile, bool isEncoding) {
	inputFile.clear();
	inputFile.seekg(0, inputFile.end);
	std::streamoff inputSize = inputFile.tellg();
	inputFile.seekg(0, inputFile.beg);

	if (inputFile.bad()) {
		throw HuffmanArchiver::ArchiverExeption("Error reading file.");
	}

	outputFile.clear();
	outputFile.seekp(0, outputFile.end);
	std::streamoff outputSize = outputFile.tellp();
	outputFile.seekp(0, outputFile.beg);

	if (outputFile.bad()) {
		throw HuffmanArchiver::ArchiverExeption("Error writing to file.");
	}

	std::size_t additional = sizeof(std::size_t) * HuffmanArchiver::ALPHABET_SIZE;

	if (isEncoding) {
		std::cout << inputSize << '\n' << outputSize - additional << '\n' << additional << '\n';
	}
	else {
		std::cout << inputSize - additional << '\n' << outputSize << '\n' << additional << '\n';
	}
}

namespace HuffmanArchiver {	
	const std::size_t BUFFER_SIZE = 1024;

	TreeNode::TreeNode(std::uint8_t symb, std::size_t freq, std::size_t index, const TreeNode *left, const TreeNode *right)
		: _symb(symb), _freq(freq), _index(index), _left(left), _right(right) {}

	bool TreeNode::operator<(const TreeNode &other) const {
		if (_freq == other._freq)
			return _symb < other._symb;
		return _freq < other._freq;
	}

	void TreeNode::setIndex(std::size_t index) {
		_index = index;
	}

	std::size_t TreeNode::getFreq() const {
		return _freq;
	}

	const TreeNode *TreeNode::getLeft() const {
		return _left;
	}

	const TreeNode *TreeNode::getRight() const {
		return _right;
	}

	std::uint8_t TreeNode::getSymb() const {
		return _symb;
	}

	HuffmanTree::HuffmanTree(const std::vector<std::size_t> &frequency) {
		for (std::size_t i = 0; i < ALPHABET_SIZE; i++) {
			if (frequency[i] != 0) {
				_tree.push_back(TreeNode((std::uint8_t)i, frequency[i]));
			}
		}

		sort(_tree.begin(), _tree.end());
		_tree.reserve(ALPHABET_SIZE * ALPHABET_SIZE);

		std::queue<std::size_t> nodes1, nodes2;

		for (std::size_t i = 0; i < _tree.size(); i++) {
			nodes1.push(i);
			_tree[i].setIndex(i);
		}

		while (nodes1.size() + nodes2.size() > 1) {
			if (nodes1.size() == 0) {
				swap(nodes1, nodes2);
			}

			TreeNode *minNode[2];

			for (std::size_t i = 0; i < 2; i++) {
				if (nodes2.size() == 0 || (nodes1.size() != 0 && _tree[nodes1.front()] < _tree[nodes2.front()])) {
					minNode[i] = &_tree[nodes1.front()];
					nodes1.pop();
				}
				else {
					minNode[i] = &_tree[nodes2.front()];
					nodes2.pop();
				}
			}

			_tree.push_back(TreeNode(0, minNode[0]->getFreq() + minNode[1]->getFreq(), _tree.size(), minNode[0], minNode[1]));
			nodes2.push(_tree.size() - 1);
		}
	}

	void HuffmanTree::generateCodes(std::vector<std::string> &codes, const TreeNode *node) {
		if (codes.size() != ALPHABET_SIZE) {
			codes.resize(ALPHABET_SIZE);
		}

		if (_tree.size() == 0) {
			return;
		}

		if (node == NULL) {
			node = &_tree.back();
		}

		if (node->getLeft() == NULL && node->getRight() == NULL) {
			codes[node->getSymb()] = (_currentCode.size() == 0 ? "0" : _currentCode);
			return;
		}

		_currentCode.push_back('0');
		generateCodes(codes, node->getLeft());
		_currentCode.pop_back();

		_currentCode.push_back('1');
		generateCodes(codes, node->getRight());
		_currentCode.pop_back();
	}

	const TreeNode *HuffmanTree::getRoot() const {
		return (_tree.size() == 0 ? NULL : &_tree.back());
	}
	
	ArchiverExeption::ArchiverExeption(const std::string &m)
		: _message(m) {}
	const char* ArchiverExeption::what() const throw() {
		return _message.c_str();
	}
	
	void countFrequency(std::istream &stream, std::vector<std::size_t> &frequency) {
		std::uint8_t buffer[BUFFER_SIZE];

		if (frequency.size() != ALPHABET_SIZE) {
			frequency.resize(ALPHABET_SIZE);
		}

		for (std::size_t i = 0; i < ALPHABET_SIZE; i++) {
			frequency[i] = 0;
		}

		while (!stream.eof()) {
			stream.read((char *)buffer, BUFFER_SIZE);

			if (stream.bad()) {
				throw ArchiverExeption("Error reading file.");
			}

			for (std::streamsize i = 0; i < stream.gcount(); i++) {
				frequency[buffer[i]]++;
			}
		}
	}

	void readFrequency(std::istream &stream, std::vector<std::size_t> &frequency) {
		if (frequency.size() != ALPHABET_SIZE) {
			frequency.resize(ALPHABET_SIZE);
		}

		stream.read((char *)frequency.data(), sizeof(size_t) * ALPHABET_SIZE);

		if (stream.bad()) {
			throw ArchiverExeption("Error reading file.");
		}
	}

	void writeFrequency(std::ostream &stream, const std::vector<std::size_t> &frequency) {
		stream.write((char *)frequency.data(), sizeof(size_t) * ALPHABET_SIZE);

		if (stream.bad()) {
			throw ArchiverExeption("Error writing to file.");
		}
	}

	void encodeData(std::istream &inputFile, std::ostream &outputFile, const std::vector<std::string> &codes) {
		std::uint8_t buffer[BUFFER_SIZE];
		outputBitStream bitStream(outputFile);

		inputFile.clear();
		inputFile.seekg(0, inputFile.beg);

		while (!inputFile.eof()) {
			inputFile.read((char *)buffer, BUFFER_SIZE);

			if (inputFile.bad()) {
				throw ArchiverExeption("Error reading file.");
			}

			for (std::streamsize i = 0; i < inputFile.gcount(); i++) {
				for (std::size_t j = 0; j < codes[buffer[i]].size(); j++) {
					bitStream.write(codes[buffer[i]][j] - '0');
				}				
			}
		}
	}

	void decodeData(std::istream &inputFile, std::ostream &outputFile, const HuffmanTree &tree) {
		if (tree.getRoot() == NULL) {
			return;
		}

		std::uint8_t buffer[BUFFER_SIZE];
		std::size_t bufferSize = 0;
		const TreeNode *node;
		std::size_t symbolsCount = tree.getRoot()->getFreq();
		std::size_t i = 0;
		inputBitStream bitStream(inputFile);

		while (i != symbolsCount) {
			node = tree.getRoot();

			while (node->getLeft() != NULL || node->getRight() != NULL) {
				char bit = bitStream.read();

				if (bit == 0) {
					node = node->getLeft();
				}
				else {
					node = node->getRight();
				}
			}

			buffer[bufferSize] = node->getSymb();
			bufferSize++;

			if (bufferSize == BUFFER_SIZE) {
				bufferSize = 0;
				outputFile.write((char *)buffer, BUFFER_SIZE);

				if (outputFile.bad()) {
					throw ArchiverExeption("Error writing to file.");
				}
			}

			i++;
		}

		outputFile.write((char *)buffer, bufferSize);

		if (outputFile.bad()) {
			throw ArchiverExeption("Error writing to file.");
		}
	}

	void encode(std::istream &inputFile, std::ostream &outputFile) {
		std::vector<std::size_t> frequency;
		HuffmanArchiver::countFrequency(inputFile, frequency);
		HuffmanArchiver::HuffmanTree tree(frequency);
		std::vector<std::string> codes;
		tree.generateCodes(codes);
		HuffmanArchiver::writeFrequency(outputFile, frequency);
		HuffmanArchiver::encodeData(inputFile, outputFile, codes);
	}

	void decode(std::istream &inputFile, std::ostream &outputFile) {
		std::vector<std::size_t> frequency;
		HuffmanArchiver::readFrequency(inputFile, frequency);
		HuffmanArchiver::HuffmanTree tree(frequency);
		HuffmanArchiver::decodeData(inputFile, outputFile, tree);
	}
}