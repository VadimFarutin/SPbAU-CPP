#include <cstring>
#include <sstream>
#include "huffman_test.h"
#include "huffman.h"

using HuffmanArchiver::TreeNode;
using HuffmanArchiver::HuffmanTree;

void HuffmanTest::testTreeNodeOperatorLess1() {
	TreeNode node1(255, 10, 0);
	TreeNode node2(25, 12, 5, NULL, NULL);

	DO_CHECK(node1 < node2);
}

void HuffmanTest::testTreeNodeOperatorLess2() {
	TreeNode node1(254, 10);
	TreeNode node2(255, 10);

	DO_CHECK(node1 < node2);
}

void HuffmanTest::testTreeNodeOperatorLess3() {
	TreeNode node1(25, 10);
	TreeNode node2(55, 120);

	DO_CHECK(node1 < node2);
}

void HuffmanTest::testTreeNodeSetIndex1() {
	TreeNode node(25, 10);
	node.setIndex(5);
	
	DO_CHECK(node._index == 5);
}

void HuffmanTest::testTreeNodeSetIndex2() {
	TreeNode node(25, 10, 7, NULL, NULL);
	node.setIndex(0);

	DO_CHECK(node._index == 0);
}

void HuffmanTest::testTreeNodeGetFreq1() {
	TreeNode node(100, 200);

	DO_CHECK(node.getFreq() == 200);
}

void HuffmanTest::testTreeNodeGetFreq2() {
	TreeNode node(100, 200, 345, NULL, NULL);

	DO_CHECK(node.getFreq() == 200);
}

void HuffmanTest::testTreeNodeGetLeft1() {
	TreeNode node(100, 200);

	DO_CHECK(node.getLeft() == NULL);
}

void HuffmanTest::testTreeNodeGetLeft2() {
	TreeNode node1(100, 200, 345, NULL, NULL);
	TreeNode node2(3, 23, 1, &node1, NULL);

	DO_CHECK(node2.getLeft() == &node1);
}

void HuffmanTest::testTreeNodeGetRight1() {
	TreeNode node(100, 200);

	DO_CHECK(node.getRight() == NULL);
}

void HuffmanTest::testTreeNodeGetRight2() {
	TreeNode node1(100, 200, 345, NULL, NULL);
	TreeNode node2(3, 23, 1, &node1, &node1);

	DO_CHECK(node2.getRight() == &node1);
}

void HuffmanTest::testTreeNodeGetSymb1() {
	TreeNode node(100, 200);

	DO_CHECK(node.getSymb() == 100);
}

void HuffmanTest::testTreeNodeGetSymb2() {
	TreeNode node(1, 200, 345, NULL, NULL);

	DO_CHECK(node.getSymb() == 1);
}

void HuffmanTest::testHuffmanTreeConstructor1() {
	std::vector<std::size_t> frequency(HuffmanArchiver::ALPHABET_SIZE);
	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		frequency[i] = 0;
	}

	frequency[1] = 200;
	frequency[2] = 4;
	frequency[3] = 4000;

	HuffmanTree tree(frequency);

	bool testPassed = true;
	
	const TreeNode *node = tree.getRoot();
	
	if (node == NULL) {
		testPassed = false;
	}

	if (node->getRight() == NULL ||
		node->getRight()->getSymb() != 3)
	{
		testPassed = false;
	}

	if (node->getLeft() == NULL ||
		node->getLeft()->getLeft() == NULL ||
		node->getLeft()->getRight() == NULL || 
		node->getLeft()->getLeft()->getSymb() != 2 || 
		node->getLeft()->getRight()->getSymb() != 1)
	{
		testPassed = false;
	}

	DO_CHECK(testPassed);
}

void HuffmanTest::testHuffmanTreeConstructor2() {
	std::vector<std::size_t> frequency(HuffmanArchiver::ALPHABET_SIZE);
	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		frequency[i] = 0;
	}

	frequency[1] = 3;
	frequency[2] = 3;
	frequency[3] = 4;
	frequency[4] = 4;

	HuffmanTree tree(frequency);

	bool testPassed = true;

	const TreeNode *node = tree.getRoot();
	
	if (node == NULL) {
		testPassed = false;
	}

	if (node->getRight() == NULL ||
		node->getRight()->getLeft() == NULL ||
		node->getRight()->getRight() == NULL ||
		node->getRight()->getLeft()->getSymb() != 3 ||
		node->getRight()->getRight()->getSymb() != 4)
	{
		testPassed = false;
	}
	
	if (node->getLeft() == NULL ||
		node->getLeft()->getLeft() == NULL ||
		node->getLeft()->getRight() == NULL ||
		node->getLeft()->getLeft()->getSymb() != 1 ||
		node->getLeft()->getRight()->getSymb() != 2)
	{
		testPassed = false;
	}

	DO_CHECK(testPassed);
}

void HuffmanTest::testHuffmanTreeGenerateCodes1() {
	std::vector<std::size_t> frequency(HuffmanArchiver::ALPHABET_SIZE);
	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		frequency[i] = 0;
	}

	frequency[1] = 200;
	frequency[2] = 4;
	frequency[3] = 4000;

	HuffmanTree tree(frequency);
	std::vector<std::string> codes;
	tree.generateCodes(codes);

	DO_CHECK(codes[2] == "00" && codes[1] == "01" && codes[3] == "1");
}

void HuffmanTest::testHuffmanTreeGenerateCodes2() {
	std::vector<std::size_t> frequency(HuffmanArchiver::ALPHABET_SIZE);
	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		frequency[i] = 0;
	}

	frequency[1] = 3;
	frequency[2] = 3;
	frequency[3] = 4;
	frequency[4] = 4;

	HuffmanTree tree(frequency);
	std::vector<std::string> codes;
	tree.generateCodes(codes);

	DO_CHECK(codes[1] == "00" && codes[2] == "01" && codes[3] == "10" && codes[4] == "11");
}

void HuffmanTest::testHuffmanTreeGetRoot1() {
	std::vector<std::size_t> frequency(HuffmanArchiver::ALPHABET_SIZE);
	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		frequency[i] = 0;
	}

	frequency[1] = 200;
	frequency[2] = 4;
	frequency[3] = 4000;

	HuffmanTree tree(frequency);
	const TreeNode *node = tree.getRoot();

	DO_CHECK(node != NULL && node->getLeft() != NULL && node->getRight() != NULL && node->getFreq() == 4204);
}

void HuffmanTest::testHuffmanTreeGetRoot2() {
	std::vector<std::size_t> frequency(HuffmanArchiver::ALPHABET_SIZE);
	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		frequency[i] = 0;
	}

	frequency[1] = 3;
	frequency[2] = 3;
	frequency[3] = 4;
	frequency[4] = 4;

	HuffmanTree tree(frequency); 
	const TreeNode *node = tree.getRoot();

	DO_CHECK(node != NULL && node->getLeft() != NULL && node->getRight() != NULL && node->getFreq() == 14);
}

void HuffmanTest::testParseArguments1() {
	int argc = 6;
	char argv[6][10];
	strcpy(argv[1], "-c");
	strcpy(argv[2], "-f");
	strcpy(argv[3], "in");
	strcpy(argv[4], "-o");
	strcpy(argv[5], "out");
	
	char *argv_p[6];
	for (std::size_t i = 0; i < 6; i++)
		argv_p[i] = &argv[i][0];

	std::string inputFile;
	std::string outputFile;
	bool isEncoding = parseArguments(argc, argv_p, inputFile, outputFile);

	DO_CHECK(isEncoding == true && inputFile == "in" && outputFile == "out");
}

void HuffmanTest::testParseArguments2() {
	int argc = 6;
	char argv[6][10];
	strcpy(argv[1], "--output");
	strcpy(argv[2], "out");
	strcpy(argv[3], "-u");
	strcpy(argv[4], "--file");
	strcpy(argv[5], "in");

	char *argv_p[6];
	for (std::size_t i = 0; i < 6; i++)
		argv_p[i] = &argv[i][0];
	
	std::string inputFile;
	std::string outputFile;
	bool isEncoding = parseArguments(argc, argv_p, inputFile, outputFile);

	DO_CHECK(isEncoding == false && inputFile == "in" && outputFile == "out");
}

void HuffmanTest::testParseArguments3() {
	int argc = 6;
	char argv[6][10];
	strcpy(argv[1], "-f");
	strcpy(argv[2], "in");
	strcpy(argv[3], "-c");
	strcpy(argv[4], "--output");
	strcpy(argv[5], "out");

	char *argv_p[6];
	for (std::size_t i = 0; i < 6; i++)
		argv_p[i] = &argv[i][0];

	std::string inputFile;
	std::string outputFile;
	bool isEncoding = parseArguments(argc, argv_p, inputFile, outputFile);

	DO_CHECK(isEncoding == true && inputFile == "in" && outputFile == "out");
}

void HuffmanTest::testPrintStatistic1() {
	std::stringstream inputFile("Hello World!");
	std::stringstream outputFile;
	std::string frequency(sizeof(std::size_t) * HuffmanArchiver::ALPHABET_SIZE, '0');

	outputFile.write(frequency.c_str(), frequency.size());
	outputFile << "kj3Ukl9%";
	
	std::stringstream stringStream;
	std::streambuf *stdoutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(stringStream.rdbuf());
	printStatistic(inputFile, outputFile, true);
	std::cout.rdbuf(stdoutBuffer);
	
	std::size_t additional = sizeof(std::size_t) * HuffmanArchiver::ALPHABET_SIZE;
	DO_CHECK(stringStream.str() == "12\n8\n" + std::to_string(additional) + "\n");
}

void HuffmanTest::testPrintStatistic2() {
	std::stringstream inputFile;
	std::stringstream outputFile("Hello World!");
	std::string frequency(sizeof(std::size_t) * HuffmanArchiver::ALPHABET_SIZE, '0');

	inputFile.write(frequency.c_str(), frequency.size());
	inputFile << "jhg38ks9";
	
	std::stringstream stringStream;
	std::streambuf *stdoutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(stringStream.rdbuf());
	printStatistic(inputFile, outputFile, false);
	std::cout.rdbuf(stdoutBuffer);
	
	std::size_t additional = sizeof(std::size_t) * HuffmanArchiver::ALPHABET_SIZE;
	DO_CHECK(stringStream.str() == "8\n12\n" + std::to_string(additional) + "\n");
}

void HuffmanTest::testPrintStatistic3() {
	std::stringstream inputFile("");
	std::stringstream outputFile;
	std::string frequency(sizeof(std::size_t) * HuffmanArchiver::ALPHABET_SIZE, '0');

	outputFile.write(frequency.c_str(), frequency.size());
	
	std::stringstream stringStream;
	std::streambuf *stdoutBuffer = std::cout.rdbuf();
	std::cout.rdbuf(stringStream.rdbuf());
	printStatistic(inputFile, outputFile, true);
	std::cout.rdbuf(stdoutBuffer);

	std::size_t additional = sizeof(std::size_t) * HuffmanArchiver::ALPHABET_SIZE;
	DO_CHECK(stringStream.str() == "0\n0\n" + std::to_string(additional) + "\n");
}

void HuffmanTest::testCountFrequency1() {
	std::size_t frequency[HuffmanArchiver::ALPHABET_SIZE];
	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		frequency[i] = 0;
	}

	std::string inputFileContent = "13phpi4u5h0235jjkkds;;%*";
	
	for (std::size_t i = 0; i < inputFileContent.size(); i++) {
		frequency[(std::uint8_t)inputFileContent[i]]++;
	}

	std::stringstream stringStream(inputFileContent);
	
	std::vector<std::size_t> result(HuffmanArchiver::ALPHABET_SIZE);
	HuffmanArchiver::countFrequency(stringStream, result);
	bool testPassed = true;

	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		if (frequency[i] != result[i]) {
			testPassed = false;
			break;
		}
	}

	DO_CHECK(testPassed);
}

void HuffmanTest::testCountFrequency2() {
	std::string inputFileContent = "";
	std::stringstream stringStream(inputFileContent);

	std::vector<std::size_t> result(HuffmanArchiver::ALPHABET_SIZE);
	HuffmanArchiver::countFrequency(stringStream, result);
	bool testPassed = true;

	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		if (result[i] != 0) {
			testPassed = false;
			break;
		}
	}

	DO_CHECK(testPassed);
}

void HuffmanTest::testReadFrequency1() {
	std::size_t frequency[HuffmanArchiver::ALPHABET_SIZE];
	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		frequency[i] = 0;
	}

	std::string inputFileContent = "13phpi4u5h0235jjkkds;;%*";

	for (std::size_t i = 0; i < inputFileContent.size(); i++) {
		frequency[(std::uint8_t)inputFileContent[i]]++;
	}

	std::stringstream stringStream;
	stringStream.write((char *)frequency, sizeof(size_t) * HuffmanArchiver::ALPHABET_SIZE);
	std::vector<std::size_t> result(HuffmanArchiver::ALPHABET_SIZE);
	HuffmanArchiver::readFrequency(stringStream, result);
	bool testPassed = true;

	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		if (frequency[i] != result[i]) {
			testPassed = false;
			break;
		}
	}

	DO_CHECK(testPassed);
}

void HuffmanTest::testReadFrequency2() {
	std::size_t frequency[HuffmanArchiver::ALPHABET_SIZE];
	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		frequency[i] = 0;
	}

	std::stringstream stringStream;
	stringStream.write((char *)frequency, sizeof(size_t) * HuffmanArchiver::ALPHABET_SIZE);
	std::vector<std::size_t> result(HuffmanArchiver::ALPHABET_SIZE);
	HuffmanArchiver::readFrequency(stringStream, result);
	bool testPassed = true;

	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		if (frequency[i] != result[i]) {
			testPassed = false;
			break;
		}
	}

	DO_CHECK(testPassed);
}

void HuffmanTest::testWriteFrequency1() {
	std::vector<std::size_t> frequency(HuffmanArchiver::ALPHABET_SIZE);
	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		frequency[i] = 0;
	}

	std::string inputFileContent = "13phpi4u5h0235jjkkds;;%*";

	for (std::size_t i = 0; i < inputFileContent.size(); i++) {
		frequency[(std::uint8_t)inputFileContent[i]]++;
	}

	std::stringstream stringStream;
	stringStream.write((char *)frequency.data(), sizeof(size_t) * HuffmanArchiver::ALPHABET_SIZE);

	std::stringstream result;
	HuffmanArchiver::writeFrequency(result, frequency);
	
	DO_CHECK(stringStream.str() == result.str());
}

void HuffmanTest::testWriteFrequency2() {
	std::vector<std::size_t> frequency(HuffmanArchiver::ALPHABET_SIZE);
	for (std::size_t i = 0; i < HuffmanArchiver::ALPHABET_SIZE; i++) {
		frequency[i] = 0;
	}
	
	std::stringstream stringStream;
	stringStream.write((char *)frequency.data(), sizeof(size_t) * HuffmanArchiver::ALPHABET_SIZE);

	std::stringstream result;
	HuffmanArchiver::writeFrequency(result, frequency);

	DO_CHECK(stringStream.str() == result.str());
}

void HuffmanTest::testEncodeData1() {
	std::stringstream inputFile("qiwghdfpw8ieyfp9wq7trp9r2(()&(&0-0-^^");
	std::stringstream outputFile;

	std::vector<std::size_t> frequency(HuffmanArchiver::ALPHABET_SIZE);
	HuffmanArchiver::countFrequency(inputFile, frequency);
	HuffmanTree tree(frequency);
	std::vector<std::string> codes;
	tree.generateCodes(codes);
	HuffmanArchiver::encodeData(inputFile, outputFile, codes);

	DO_CHECK(outputFile.str() == "©á\f\x11½ü„±­Õñ/ZýÌððÕ\x15\x1dÀ");
}

void HuffmanTest::testEncodeData2() {
	std::stringstream inputFile("");
	std::stringstream outputFile;

	std::vector<std::size_t> frequency(HuffmanArchiver::ALPHABET_SIZE);
	HuffmanArchiver::countFrequency(inputFile, frequency);
	HuffmanTree tree(frequency);
	std::vector<std::string> codes;
	tree.generateCodes(codes);
	HuffmanArchiver::encodeData(inputFile, outputFile, codes);

	DO_CHECK(outputFile.str() == "");
}

void HuffmanTest::testDecodeData1() {
	std::stringstream encodeStream("qiwghdfpw8ieyfp9wq7trp9r2(()&(&0-0-^^");
	std::vector<std::size_t> freqIn(HuffmanArchiver::ALPHABET_SIZE);
	HuffmanArchiver::countFrequency(encodeStream, freqIn);
	std::stringstream inputFile;
	HuffmanArchiver::writeFrequency(inputFile, freqIn);
	inputFile << "©á\f\x11½ü„±­Õñ/ZýÌððÕ\x15\x1dÀ";
	std::stringstream outputFile;

	std::vector<std::size_t> freqOut(HuffmanArchiver::ALPHABET_SIZE);
	HuffmanArchiver::readFrequency(inputFile, freqOut);
	HuffmanTree tree(freqOut);
	HuffmanArchiver::decodeData(inputFile, outputFile, tree);

	DO_CHECK(outputFile.str() == "qiwghdfpw8ieyfp9wq7trp9r2(()&(&0-0-^^");
}

void HuffmanTest::testDecodeData2() {
	std::stringstream encodeStream("");
	std::vector<std::size_t> freqIn(HuffmanArchiver::ALPHABET_SIZE);
	HuffmanArchiver::countFrequency(encodeStream, freqIn);
	std::stringstream inputFile;
	HuffmanArchiver::writeFrequency(inputFile, freqIn);
	std::stringstream outputFile;

	std::vector<std::size_t> freqOut(HuffmanArchiver::ALPHABET_SIZE);
	HuffmanArchiver::readFrequency(inputFile, freqOut);
	HuffmanTree tree(freqOut);
	HuffmanArchiver::decodeData(inputFile, outputFile, tree);

	DO_CHECK(outputFile.str() == "");
}

void HuffmanTest::runAllTests() {
	testTreeNodeOperatorLess1();
	testTreeNodeOperatorLess2();
	testTreeNodeOperatorLess3();
	testTreeNodeSetIndex1();
	testTreeNodeSetIndex2();
	testTreeNodeGetFreq1();
	testTreeNodeGetFreq2();
	testTreeNodeGetLeft1();
	testTreeNodeGetLeft2();
	testTreeNodeGetRight1();
	testTreeNodeGetRight2();
	testTreeNodeGetSymb1();
	testTreeNodeGetSymb2();

	testHuffmanTreeConstructor1();
	testHuffmanTreeConstructor2();
	testHuffmanTreeGenerateCodes1();
	testHuffmanTreeGenerateCodes2();
	testHuffmanTreeGetRoot1();
	testHuffmanTreeGetRoot2();

	testParseArguments1();
	testParseArguments2();
	testParseArguments3();

	testPrintStatistic1();
	testPrintStatistic2();
	testPrintStatistic3();

	testCountFrequency1();
	testCountFrequency2();

	testReadFrequency1();
	testReadFrequency2();

	testWriteFrequency1();
	testWriteFrequency2();

	testEncodeData1();
	testEncodeData2();

	testEncodeData1();
	testEncodeData2();
}