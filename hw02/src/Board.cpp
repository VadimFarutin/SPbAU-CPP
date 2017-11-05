#include "Board.h"
#include <algorithm>

Board::Board() {
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			board[i][j] = FREE_CELL;
}

void Board::move(int x, int y, char sign) {
	board[x][y] = sign;
}

bool Board::canMove(int x, int y) const {
	return x >= 0 && x < BOARD_SIZE &&
		y >= 0 && y < BOARD_SIZE &&
		board[x][y] == FREE_CELL;
}

bool Board::isPlayerWin(char sign) const {
#define PAIR std::pair<int, int>
	PAIR directions[] = { PAIR(0, 1), PAIR(1, 0), PAIR(1, 1), PAIR(1, -1) };
#undef PAIR

	for (int i = 0; i < 4; i++) {
		for (int start_x = 0; start_x < BOARD_SIZE; start_x++) {
			for (int start_y = 0; start_y < BOARD_SIZE; start_y++) {
				bool found = true;
				int x = start_x;
				int y = start_y;

				for (int j = 0; j < 5; j++) {
					if (x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board[x][y] != sign)
						found = false;

					x += directions[i].first;
					y += directions[i].second;
				}

				if (found)
					return true;
			}
		}
	}

	return false;
}

bool Board::isBoardFull() const {
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (board[i][j] == FREE_CELL)
				return false;

	return true;
}

State Board::isWin() const {
	if (isPlayerWin(X_CELL))
		return X_WIN;

	if (isPlayerWin(O_CELL))
		return O_WIN;

	if (isBoardFull())
		return DRAW;

	return GAME_IN_PROGRESS;
}

char Board::getCell(int x, int y) const {
	return board[x][y];
}
