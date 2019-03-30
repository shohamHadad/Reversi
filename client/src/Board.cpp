#include "../include/Board.h"
#include <iostream>
using namespace std;

/**
 * function name: Board
 * input: the board's size
 * output: new object of board
 * operation: constructor
 */
Board::Board(int s) {
	size = s;
	array = vector<vector<Square*> >(size, vector<Square*> (size));
	for (int i = 0; i < size; i++) {
		array[i] = vector<Square*>(size);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			array[i][j] = new Square(i, j);
		}
	}

	array[size/2 -1][size/2 -1]->setType('O');
	array[size/2][size/2]->setType('O');
	array[size/2 - 1][size/2]->setType('X');
	array[size/2][size/2 - 1]->setType('X');
}

/**
 * function name: Board
 * input: original board
 * output:copy object of board
 * operation:copy constructor
 */
Board::Board(const Board &board){
	size = board.size;
	array = vector<vector<Square*> >(board.size, vector<Square*> (board.size));
	for (int i = 0; i < size; i++) {
		array[i] = vector<Square*>(size);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			array[i][j] = new Square(i, j);
		}
	}
    for (int k = 0; k < size; k++) {
        for (int l = 0; l < size; l++) {
            array[k][l]->setType(board.getType(k, l));
        }

    }
}

/**
 * function name: ~Board
 * input: void
 * output: void
 * operation: destructor
 */
Board::~Board() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			delete array[i][j];
		}
	}
}

/**
 * function name: drawLine
 * input: void
 * output: void
 * operation: draws the separate line in the board.
 */
void Board::drawLine() {
	for (int i = 0; i < size * 4 + 2; i++) {
		cout << "-";
	}
	cout << endl;
}

/**
 * function name: print
 * input: void
 * output: void
 * operation: print out the board
 */
void Board::print() {
	cout << endl;
	for (int i = 0; i < size + 1; i++) {
		for (int j = 0; j < size + 1; j++) {
			if (i == 0) {
				if (j == 0) {
					continue;
				}
				cout << " | " << j;
				if (j == size) {
					cout << " |" << endl;
					drawLine();
					continue;
				}
			} else if (j == 0) {
				cout << i << "|";
			} else {
				cout << " " << this->array[i - 1][j - 1]->getType() << " |";
			}
			if (j == size) {
				cout << endl;
				drawLine();
			}
		}
	}
}

/**
 * function name: get type
 * input: x and y indexes
 * output: char
 * operation: returns the state of the given location in the array
 */
char Board::getType(int i, int j) const {
	return array[i][j]->getType();
}

/**
 * function name: isEmpty
 * input: x and y indexes of the board's array
 * output: boolean
 * operation: checks if the given location is empty
 */
bool Board::isEmpty(int x, int y){
	if (array[x][y]->getType() == ' ') {
		return true;
	}
	return false;
}

/**
 * function name: isOutOfBounderies
 * input: x and y indexes
 * output: boolean
 * operation: checks if the given location is out of the array's boundaries
 */
bool Board::isOutOfBounderies(int x, int y){
	if (x < 0 || x >= size || y < 0 || y >= size) {
		return true;
	}
	return false;
}

/**
 * function name: isBoardFull
 * input: void
 * output: boolean
 * operation: checks if the board is full
 */
bool Board::isBoardFull() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (array[i][j]->getType() == ' ') {
				return false;
			}
		}
	}
	return true;
}

/**
 * function name: getSize
 * input: void
 * output: int
 * operation: returns the board's size
 */
int Board::getSize() {
	return size;
}

void Board::setType(int i, int j, char newType) {
	array[i][j]->setType(newType);
}
/**
 * function name: whoWin
 * input: void
 * output: Winner
 * operation: checks who won - X, O or it's a tie.
 */
Winner Board::whoWin() {
	int x = 0;
	int o = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (array[i][j]->getType() == 'X') {
				x++;
			} else if (array[i][j]->getType() == 'O') {
				o++;
			}
		}
	}
	if (x > o) {
		return X;
	} else if (o > x) {
		return O;
	} else {
		return tie;
	}
}

/**
 * function name: numOfX
 * input: void
 * output: number of x's in the board.
 * operation: the function counts number of x's in the board.
 */
int Board::numOfX(){
	int x = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (array[i][j]->getType() == 'X') {
				x++;
			}
		}
	}
	return x;
}
