#pragma once

#include "Board.h"

class BoardView {
public:
    BoardView(Board &board);
    void showBoard() const;
    void doGameCycle(bool isSilent);

private:
	Board &board;
};
