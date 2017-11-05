#pragma once

#include "Board.h"

class NcursesBoardView {
public:
    NcursesBoardView(Board &board);
    void showBoard() const;
    void doGameCycle();

private:
	Board &board;
};
