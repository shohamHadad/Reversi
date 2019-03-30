#include "../include/RemotePlayer.h"
/**
 * function name: RemotePlayer()
 * input: void
 * output: new RemotePlayer
 * operation: constructor
 */
RemotePlayer::RemotePlayer() {
}

/**
 * function name: ~RemotePlayer()
 * input: void
 * output: delete RemotePlayer
 * operation: destructor
 */
RemotePlayer::~RemotePlayer() {
}

/**
 * function name: chooseSquare()
 * input: vector<Square>
 * output: Square
 * operation: returns the next move of RemotePlayer as read from socket
 */
Square RemotePlayer::chooseSquare(vector<Square> possibleMoves, Player* current, Player* opponent) {
	cout << "Waiting for other player's move..." << endl;
	return opponent->getNextMove();
}
