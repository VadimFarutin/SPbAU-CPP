#include "BoardView.h"
#include <cstdio>

BoardView::BoardView(Board &board)
	: board(board) {}

void BoardView::showBoard() const {
	printf("\n");
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			printf("%c", board.getCell(i, j));
		printf("\n");
	}
}

void BoardView::doGameCycle(bool isSilent) {
	char currentPlayer = O_CELL;
	int x, y;

	while (board.isWin() == GAME_IN_PROGRESS) {
		if (!isSilent)
			showBoard();

		while (true) {
			printf("%c move: ", currentPlayer);

			if (scanf("%i %i", &x, &y) == 2) {
				if (x == -1 && y == -1)
					return;

				if (board.canMove(x, y))
					break;
			}

			printf("Bad move!\n");
		}

		board.move(x, y, currentPlayer);

		if (currentPlayer == O_CELL)
			currentPlayer = X_CELL;
		else
			currentPlayer = O_CELL;
	}

	showBoard();

	State result = board.isWin();
	if (result == O_WIN)
		printf("O wins!\n");
	else if (result == X_WIN)
		printf("X wins!\n");
	else
		printf("Draw.\n");
}
