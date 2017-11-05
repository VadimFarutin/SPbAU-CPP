#include "BoardTest.h"
#include <cstdio>

int main() {
    BoardTest boardTest;
    boardTest.runAllTests();
    BoardTest::showFinalResult();

    return 0;
}
