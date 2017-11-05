#include "Test.h"
#include <cstdio>

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char  *filename, size_t lineNum) {
	if (!expr) {
		printf("test failed: %s in %s:%lu\n", func, filename, lineNum);
		Test::failedNum++;
	}

	Test::totalNum++;
}

void Test::showFinalResult() {
	if (Test::failedNum == 0)
		printf("All tests passed.\n");
	else
		printf("Failed %i of %i tests.\n", Test::failedNum, Test::totalNum);
}
