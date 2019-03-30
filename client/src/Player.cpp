#include "../include/Player.h"
#include <iostream>
#include <limits>
using namespace std;

/**
 * function name: Player
 * input: char
 * output: new object of player
 * operation: constructor
 */
Player::Player(char type): type(type) {}


/**
 * function name: ~Player
 * input: void
 * output: void
 * operation: destructor
 */
Player::~Player(){}

/**
 * function name: chooseSquare
 * input: vector<Square>
 * output: Square
 * operation: get a valid move from the user and returns it
 */
Square Player::chooseSquare(vector<Square> possibleMoves, Player* current, Player* opponent) {

}

/**
 * function name: getNextMove
 * input: void
 * output: Square
 * operation: get the next move from the opponent
 */
Square Player::getNextMove() {

}

/**
 * function name: noMove
 * input: void
 * output: void
 * operation: print out the noMove message and send "NoMove" message to server
 */
void Player::noMove(Player* current, Player* opponent) {
	cout << current->getType() << " Has no possible moves. Play passes back to " << opponent->getType()
		 << endl;
}

/**
 * function name: endGame
 * input: void
 * output: void
 * operation: send "End" message to server
 */
void Player::endGame() {

}

/**
 * function name: getType
 * input: void
 * output: char
 * operation: the player's type (X or O)
 */
char Player::getType() {
	return type;
}

/**
 * function name: equals
 * input: Player*
 * output: boolean
 * operation: checks if the other player equals to this player.
 */
bool Player::equals(Player* other) {
	if (this->type == other->type) {return true;}
	return false;
}

/**
 * function name: setType
 * input: void
 * output: void
 * operation: set the type
 */
void Player::setType(char t) {
	type = t;
}
