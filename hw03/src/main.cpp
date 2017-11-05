#include <iostream>
#include "huffman.h"

int main(int argc, char **argv) {
	std::string inputFile;
	std::string outputFile;
	std::fstream ifs;
	std::fstream ofs;
		
	try {
		bool isEncoding = parseArguments(argc, argv, inputFile, outputFile);
		openFile(ifs, inputFile, std::ios::in);
		openFile(ofs, outputFile, std::ios::out);

		if (isEncoding) {
			HuffmanArchiver::encode(ifs, ofs);
		}
		else {
			HuffmanArchiver::decode(ifs, ofs);
		}

		printStatistic(ifs, ofs, isEncoding);
	}
	catch (const std::exception &e) {
		std::cout << e.what() << '\n';
	}

	return 0;
}