#include "../include/GameLogic.h"
#include <iostream>

using namespace std;

/**
 * function name: GameLogic
 * input: board object
 * output: new GameLogic object
 * operation: constructor
 */
GameLogic::GameLogic(Board* board): turns(0) {
	this->board = board;
}

/**
 * function name: GameLogic
 * input: board object
 * output: copy GameLogic object
 * operation: copy constructor
 */
GameLogic::GameLogic(const GameLogic &gameLogic) {
    board =  new Board(*gameLogic.getBoard());
}
/**
 * function name: ~GameLogic
 * input: void
 * output: void
 * operation: destructor
 */
GameLogic::~GameLogic() {
	delete board;
}

/**
 * function name: possibleMoves
 * input: the players
 * output: a vector of the possible moves (squares)
 * operation: get all the current player's possible moves
 */
vector<Square> GameLogic::possibleMoves(Player* current, Player* opponent){
	vector<Square> moves;
	// go over the board
	for (int i = 0; i < board->getSize(); i++) {
		for (int j = 0; j < board->getSize(); j++) {
			// if the cell dosn't exist or is not empty, continue
			if (board->isOutOfBounderies(i,j) || board->getType(i,j) != ' ') {
				continue;
			}
			// if it's a valid move, push it in the vector
			if (isPossibleMove(i, j, current, opponent)) {
				moves.push_back(Square(i+1, j+1));
			}
		}
	}
	return moves;
}

/**
 * function name: isPossibleMove
 * input: location and 2 players
 * output: boolean
 * operation: check the given location's each direction and returns true if any of them is valid
 */
bool GameLogic::isPossibleMove(int x, int y ,Player* current, Player* opponent) {
	// check upper left
	if (checkDirection(current, opponent, x-1, y-1, -1, -1, 0)) {
		return true;
	}
	// check upper mid
	if (checkDirection(current, opponent, x-1, y, -1, 0, 0)) {
		return true;
	}
	// check upper right
	if (checkDirection(current, opponent, x-1, y+1, -1, 1, 0)) {
		return true;
	}
	// check mid left
	if (checkDirection(current, opponent, x, y-1, 0, -1, 0)) {
		return true;
	}
	// check mid right
	if (checkDirection(current, opponent, x, y+1, 0, 1, 0)) {
		return true;
	}
	// check lower left
	if (checkDirection(current, opponent, x+1, y-1, 1, -1, 0)) {
		return true;
	}
	// check lower mid
	if (checkDirection(current, opponent, x+1, y, 1, 0, 0)) {
		return true;
	}
	// check mid right
	if (checkDirection(current, opponent, x+1, y+1, 1, 1, 0)) {
		return true;
	}
	return false;
}

/**
 * function name: checkDirection
 * input: 2 players, location, direction, counter of length
 * output: boolean
 * operation: recursive function that checks if a certain direction is valid.
 */
bool GameLogic::checkDirection(Player* current, Player* opponent, int x, int y, int dx, int dy, int length) {
	// if this cell is out of bounderies, or empty,
	// or it's our cell but we didn't pass any opponent's cells on the way
	if (board->isOutOfBounderies(x, y) || board->isEmpty(x, y)
			|| (board->getType(x,y) == current->getType() && length == 0)) {
		return false;
	}
	// if we've reached our own cell
	// (and there was an opponent's cell on our way)
	if (board->getType(x,y) == current->getType()) {
		return true;
	}
	// if this is an opponent's cell
	return checkDirection(current, opponent, x+dx, y+dy, dx, dy, length+1);
}

/**
 * function name: flipInRightDirection
 * input: 2 players, location and direction
 * output: boolean
 * operation: recursive function that flips the cells in a certain location, if valid.
 */
bool GameLogic::flipInRightDirection(Player* current, Player* opponent, int x, int y, int dx, int dy) {
	// if this cell is out of bounderies or empty
	if (board->isOutOfBounderies(x, y) || board->isEmpty(x, y)) {
		return false;
	}
	// if we've reached our own cell
	// (and there was an opponent's cell on our way)
	if (board->getType(x,y) == current->getType()) {
		return true;
	}
	// if this direction is good - it's the opponent's cell
	if (flipInRightDirection(current, opponent, x+dx, y+dy, dx, dy)) {
		// flip the disk
		board->setType(x, y, current->getType());
		return true;
	} else {
		return false;
	}
}

/**
 * function name: turnDisks
 * input: 2 players, move (Square)
 * output: void
 * operation: turns the disks in all the valid directions around the given move.
 */
void GameLogic::turnDisks(Player* current, Player* opponent, Square move) {
	int x = move.getX()-1;
	int y = move.getY()-1;
	// check upper left
	if (flipInRightDirection(current, opponent, x-1, y-1, -1, -1)) {
		board->setType(x, y, current->getType());
	}
	// check upper mid
	if (flipInRightDirection(current, opponent, x-1, y, -1, 0)) {
		board->setType(x, y, current->getType());
	}
	// check upper right
	if (flipInRightDirection(current, opponent, x-1, y+1, -1, 1)) {
		board->setType(x, y, current->getType());
	}
	// check mid left
	if (flipInRightDirection(current, opponent, x, y-1, 0, -1)) {
		board->setType(x, y, current->getType());
	}
	// check mid right
	if (flipInRightDirection(current, opponent, x, y+1, 0, 1)) {
		board->setType(x, y, current->getType());
	}
	// check lower left
	if (flipInRightDirection(current, opponent, x+1, y-1, 1, -1)) {
		board->setType(x, y, current->getType());
	}
	// check lower mid
	if (flipInRightDirection(current, opponent, x+1, y, 1, 0)) {
		board->setType(x, y, current->getType());
	}
	// check mid right
	if (flipInRightDirection(current, opponent, x+1, y+1, 1, 1)) {
		board->setType(x, y, current->getType());
	}
}


/**
 * function name: playOneTurn
 * input: 2 players
 * output: void
 * operation: prints out the board, get the player's next move and operates it
 */
void GameLogic::playOneTurn(Player* current, Player* opponent) {
	// check if there are possible moves
	vector<Square> moves = possibleMoves(current, opponent);
	if (moves.empty()) {
		current->noMove(current, opponent);
        this->turns++;
		return;
	}
	// get the player's next move
	Square nextMove = current->chooseSquare(moves, current, opponent);
	// make the move
	turnDisks(current, opponent, nextMove);
	// print the move
	board->print();
	cout << current->getType() << " Played ";
	nextMove.print();
	cout << endl << endl;
	// update turn
	turns++;
}

/**
 * function name: printBoard
 * input: void
 * output: void
 * operation: prints out the board.
 */
void GameLogic::printBoard() {
	board->print();
}


/**
 * function name: gameShouldStop
 * input: 2 players
 * output:boolean
 * operation: check if the board is full or if both players can't make any more moves
 */
bool GameLogic::gameShouldStop(Player* X, Player* O) {
	if (possibleMoves(X,O).empty() && possibleMoves(O,X).empty()) {
		cout << "No more possible moves for both players." << endl;
		return true;
	}
	if (board->isBoardFull()) {
		return true;
	}
	return false;
}

/**
 * function name: whosTurn
 * input: 2 players
 * output: Player
 * operation: returns the player who's turn it is
 */
Player* GameLogic::whosTurn(Player* X, Player* O) {
	if (turns % 2 == 0) {
		return X;
	}
	return O;
}

/**
 * function name: endGame
 * input: void
 * output: void
 * operation: prints out the game result
 */
void GameLogic::endGame(Player* p1, Player* p2) {
	cout << "Game is over.";
	Winner result = board->whoWin();
	if (result == O) {
		cout << " O wins." << endl;
	} else if (result == X) {
		cout << " X wins." << endl;
	} else {
		cout << " No one wins - it's a tie." << endl;
	}
	p1->endGame();
	p2->endGame();
}
/**
 * function name: getBoard
 * input: Board*
 * output: board of the game.
 * operation: returns the board of the game.
 */
Board* GameLogic::getBoard() const{
    return this->board;
}
