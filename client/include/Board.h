#ifndef BOARD_H_
#define BOARD_H_
#include "Square.h"
#include <vector>
using namespace std;
enum Winner{X, O, tie};

/**
 * the board of the game.
 */
class Board {
private:
	int size;
	void drawLine();
	vector< vector<Square*> > array;

public:
	Board(int s = 8);
	Board(const Board &board);
	void print();
	~Board();
	int getSize();
	bool isEmpty(int, int);
	bool isOutOfBounderies(int, int);
	char getType(int, int)const;
	void setType(int, int, char);
	bool isBoardFull();
	Winner whoWin();
	int numOfX();

};

#endif /* BOARD_H_ */
