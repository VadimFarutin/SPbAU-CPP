#pragma once

#define BOARD_SIZE 10
#define FREE_CELL '.'
#define O_CELL 'O'
#define X_CELL 'X'

enum State {
	GAME_IN_PROGRESS,
	DRAW,
	O_WIN,
	X_WIN,
	STATE_COUNT
};

class  Board {
public:
	Board();
	void move(int x, int y, char sign);
	bool canMove(int x, int y) const;
	State isWin() const;
	char getCell(int x, int y) const;

private:
	char board[BOARD_SIZE][BOARD_SIZE];

	bool isPlayerWin(char sign) const;
	bool isBoardFull() const;
};
