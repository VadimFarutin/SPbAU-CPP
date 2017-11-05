#include "autotest.h"
#include <iostream>

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char *filename, size_t lineNum) {
	if (!expr) {
		Test::failedNum++;
		std::cout << "test failed: " << func << " in " << filename << ":" << lineNum << "\n";
	}

	Test::totalNum++;
}

void Test::showFinalResult() {
	if (Test::failedNum == 0) {
		std::cout << "All tests passed.\n";
	}
	else {
		std::cout << "Failed " << Test::failedNum << " of " << Test::totalNum << " tests.\n";
	}
}
