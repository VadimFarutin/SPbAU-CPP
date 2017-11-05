#pragma once

#include "Test.h"

class BoardTest: public Test {
public:
    void testIsWin1();
    void testIsWin2();
    void testIsWin3();
    void testIsWin4();

    void testMove1();
    void testMove2();
    void testMove3();

	void testCanMove1();
	void testCanMove2();
	void testCanMove3();
	void testCanMove4();

	void testGetCell1();
	void testGetCell2();
	void testGetCell3();

    void runAllTests();
};
