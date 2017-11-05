#include "BoardTest.h"
#include "Board.h"

void BoardTest::testIsWin1() {
	Board board;

	board.move(0, 0, X_CELL);
	board.move(0, 1, X_CELL);
	board.move(1, 0, X_CELL);
	board.move(4, 5, O_CELL);
	board.move(5, 5, O_CELL);

	DO_CHECK(board.isWin() == GAME_IN_PROGRESS);
}

void BoardTest::testIsWin2() {
	Board board;

	board.move(0, 0, X_CELL);
	board.move(0, 1, X_CELL);
	board.move(0, 2, X_CELL);
	board.move(0, 3, X_CELL);
	board.move(0, 4, X_CELL);

	board.move(1, 0, X_CELL);
	board.move(4, 5, O_CELL);
	board.move(5, 5, O_CELL);
	board.move(6, 5, O_CELL);
	board.move(7, 5, O_CELL);

	DO_CHECK(board.isWin() == X_WIN);
}

void BoardTest::testIsWin3() {
	Board board;

	board.move(0, 0, O_CELL);
	board.move(1, 1, O_CELL);
	board.move(2, 2, O_CELL);
	board.move(3, 3, O_CELL);
	board.move(4, 4, O_CELL);

	board.move(1, 0, X_CELL);
	board.move(4, 5, O_CELL);
	board.move(3, 5, X_CELL);
	board.move(6, 2, O_CELL);
	board.move(7, 5, X_CELL);

	DO_CHECK(board.isWin() == O_WIN);
}

void BoardTest::testIsWin4() {
	Board board;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board.move(i, j, ((i + 1) % 5 == 0 ? O_CELL : X_CELL));
			board.move(i, ++j, ((i + 1) % 5 == 0 ? X_CELL : O_CELL));
		}
	}

	DO_CHECK(board.isWin() == DRAW);
}

void BoardTest::testMove1() {
	Board board;

	board.move(0, 0, X_CELL);

	DO_CHECK(board.canMove(0, 0) == false);
}

void BoardTest::testMove2() {
	Board board;

	board.move(9, 9, O_CELL);

	DO_CHECK(board.canMove(9, 9) == false);
}

void BoardTest::testMove3() {
	Board board;

	board.move(0, 0, X_CELL);

	DO_CHECK(board.canMove(1, 1) == true);
}

void BoardTest::testCanMove1() {
	Board board;

	DO_CHECK(board.canMove(BOARD_SIZE, BOARD_SIZE) == false);
}

void BoardTest::testCanMove2() {
	Board board;

	DO_CHECK(board.canMove(BOARD_SIZE - 1, BOARD_SIZE - 1) == true);
}

void BoardTest::testCanMove3() {
	Board board;

	DO_CHECK(board.canMove(0, 0) == true);
}

void BoardTest::testCanMove4() {
	Board board;

	DO_CHECK(board.canMove(4, 5) == true);
}

void BoardTest::testGetCell1() {
	Board board;

	board.move(0, 0, X_CELL);

	DO_CHECK(board.getCell(0, 0) == X_CELL);
}

void BoardTest::testGetCell2() {
	Board board;

	board.move(5, 2, O_CELL);

	DO_CHECK(board.getCell(5, 2) == O_CELL);
}

void BoardTest::testGetCell3() {
	Board board;

	DO_CHECK(board.getCell(2, 7) == FREE_CELL);
}

void BoardTest::runAllTests() {
	testIsWin1();
	testIsWin2();
	testIsWin3();
	testIsWin4();

	testMove1();
	testMove2();
	testMove3();

	testCanMove1();
	testCanMove4();
	testCanMove4();
	testCanMove4();

	testGetCell1();
	testGetCell2();
	testGetCell3();
}
