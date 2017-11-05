#ifndef _HUFFMAN_TEST_H_
#define _HUFFMAN_TEST_H_

#include "autotest.h"

namespace HuffmanArchiver {
	class TreeNode;
}

class HuffmanTest: public Test {
public:
	void testTreeNodeOperatorLess1();
	void testTreeNodeOperatorLess2();
	void testTreeNodeOperatorLess3();
	void testTreeNodeSetIndex1();
	void testTreeNodeSetIndex2();
	void testTreeNodeGetFreq1();
	void testTreeNodeGetFreq2();
	void testTreeNodeGetLeft1();
	void testTreeNodeGetLeft2();
	void testTreeNodeGetRight1();
	void testTreeNodeGetRight2();
	void testTreeNodeGetSymb1();
	void testTreeNodeGetSymb2();

	void testHuffmanTreeConstructor1();
	void testHuffmanTreeConstructor2();
	void testHuffmanTreeGenerateCodes1();
	void testHuffmanTreeGenerateCodes2();
	void testHuffmanTreeGetRoot1();
	void testHuffmanTreeGetRoot2();

	void testParseArguments1();
	void testParseArguments2();
	void testParseArguments3();

	void testPrintStatistic1();
	void testPrintStatistic2();
	void testPrintStatistic3();

	void testCountFrequency1();
	void testCountFrequency2();

	void testReadFrequency1();
	void testReadFrequency2();

	void testWriteFrequency1();
	void testWriteFrequency2();

	void testEncodeData1();
	void testEncodeData2();

	void testDecodeData1();
	void testDecodeData2();

	void runAllTests();
};

#endif