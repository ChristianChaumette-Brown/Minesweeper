#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <Cell.h>
#include <BoardGame.h>

//enum MouseButton {left, right, unknown};

class Minesweeper: public BoardGame{
    Minesweeper();
public:
int col;
int row;
int numBomb;
int numFlags;
bool blownup;
bool cleared;
void sweep(int, int);
Minesweeper(int, int, int);
void bombSeeding();
void neighborhood();
std::vector<std::vector<Cell>> Board;
	 virtual void reset();

	 virtual void handle(int, int, MouseButton);

	 virtual ucm::json getBoard();

	 // ~Minesweeper();
};

#endif