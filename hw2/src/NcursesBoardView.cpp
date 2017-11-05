#include "NcursesBoardView.h"
#include <ncurses.h>

#include <cstdio>

NcursesBoardView::NcursesBoardView(Board &board)
	: board(board) {}

void NcursesBoardView::showBoard() const {
	move(0, 0);
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			printw("%c", board.getCell(i, j));
		printw("\n");
	}
}

void NcursesBoardView::doGameCycle() {
	initscr();
	keypad(stdscr, TRUE);
	noecho();

	char currentPlayer = O_CELL;
	int x = 0, y = 0;

	while (board.isWin() == GAME_IN_PROGRESS) {
		showBoard();

		while (true) {
			move(x, y);

			int ch = getch();

			if (ch == 'x') {
				refresh();
				endwin();
				return;
			}

			if (ch == KEY_UP && x > 0)
				x--;
			else if (ch == KEY_DOWN && x < BOARD_SIZE - 1)
				x++;
			else if (ch == KEY_LEFT && y > 0)
				y--;
			else if (ch == KEY_RIGHT && y < BOARD_SIZE - 1)
				y++;
			else if (ch == ' ') {
				if (board.canMove(x, y))
					break;
			}
		}

		board.move(x, y, currentPlayer);

		if (currentPlayer == O_CELL)
			currentPlayer = X_CELL;
		else
			currentPlayer = O_CELL;

		refresh();
	}

	showBoard();

	State result = board.isWin();
	if (result == O_WIN)
		printw("O wins!\n");
	else if (result == X_WIN)
		printw("X wins!\n");
	else
		printw("Draw.\n");

	getch();
	refresh();
	endwin();
}
