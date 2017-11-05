#include "Board.h"
#include "BoardView.h"
#include "NcursesBoardView.h"
#include <cstring>
#include <cstdio>

int main(int argc, char** argv) {
	bool isCurses = false;
	bool isSilent = false;

	if (argc > 1) {
		if (strcmp(argv[1], "silent") == 0)
			isSilent = true;
		else if (strcmp(argv[1], "curses") == 0)
			isCurses = true;
		else {
			printf("Unknown command.\n");
			return 0;
		}
	}

	if (argc == 3) {
		if (strcmp(argv[2], "silent") == 0)
			isSilent = true;
		else if (strcmp(argv[2], "curses") == 0)
			isCurses = true;
		else {
			printf("Unknown command.\n");
			return 0;
		}
	}

	if (argc > 3) {
		printf("Too much arguments(%i).\n", argc - 1);
		return 0;
	}

	Board board;
	if (isCurses) {
		NcursesBoardView boardView(board);
		boardView.doGameCycle();
	}
	else {
		BoardView boardView(board);
		boardView.doGameCycle(isSilent);
	}

	return 0;
}
