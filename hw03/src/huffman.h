#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <exception>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <cstddef>
#include <memory>
#include "huffman_test.h"

class HuffmanTest;

bool parseArguments(int argc, char **argv, std::string &inputFile, std::string &outputFile);
void openFile(std::fstream &stream, const std::string &filename, std::ios_base::openmode mode);
void printStatistic(std::istream &inputFile, std::ostream &outputFile, bool isEncoding);

namespace HuffmanArchiver {
	const std::size_t ALPHABET_SIZE = 256;

	class TreeNode {
	public:
		TreeNode(std::uint8_t symb, std::size_t freq, std::size_t index = 0, const TreeNode *left = NULL, const TreeNode *right = NULL);
		bool operator<(const TreeNode &other) const;
		void setIndex(std::size_t index);
		std::uint8_t getSymb() const;
		std::size_t getFreq() const;
		const TreeNode *getLeft() const;
		const TreeNode *getRight() const;

		friend HuffmanTest;
		
	private:
		std::uint8_t _symb;
		std::size_t _freq;
		std::size_t _index;
		const TreeNode *_left, *_right;
	};

	class HuffmanTree {
	public:
		HuffmanTree(const std::vector<std::size_t> &frequency);
		void generateCodes(std::vector<std::string> &codes, const TreeNode *node = NULL);
		const TreeNode *getRoot() const;

	private:
		std::vector<TreeNode> _tree;
		std::string _currentCode;
	};

	class ArchiverExeption : public std::exception {
	public:
		ArchiverExeption(const std::string& _m);
		~ArchiverExeption() throw() {}
		const char* what() const throw();

	private:
		std::string _message;
	};

	void countFrequency(std::istream &stream, std::vector<std::size_t> &frequency);
	void readFrequency(std::istream &stream, std::vector<std::size_t> &frequency);
	void writeFrequency(std::ostream &stream, const std::vector<std::size_t> &frequency);
	void encodeData(std::istream &inputFile, std::ostream &outputFile, const std::vector<std::string> &codes);
	void decodeData(std::istream &inputFile, std::ostream &outputFile, const HuffmanTree &tree);
	void encode(std::istream &inputFile, std::ostream &outputFile);
	void decode(std::istream &inputFile, std::ostream &outputFile);
}

#endif