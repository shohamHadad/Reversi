#include "../include/AIPlayer.h"

/**
 * function name: AIPlayer()
 * input: char, GameLogic*
 * output: AIPlayer
 * operation: constructor
 */
AIPlayer::AIPlayer(char type, GameLogic* gl): Player(type){
    gameLogic = gl;
}

/**
 * function name: ~AIPlayer()
 * input: void
 * output: void
 * operation: destructor
 */
AIPlayer::~AIPlayer() {
}

/**
 * function name: chooseSquare()
 * input: vector<Square>
 * output: Square
 * operation: get a valid move from the user and returns it
 */
Square AIPlayer::chooseSquare(vector<Square> possibleMoves, Player* current, Player* opponent) {
	vector <Square> opponentMoves;
    vector<int> grade;
    vector<int> gradeFinal;
    int xBefore, xAfter;
    // go over possibleMoves
    for (unsigned int i = 0; i < possibleMoves.size(); i++) {
        GameLogic gCopy(*getGameLogic());
        // turn the disks of the i'th move
        gCopy.turnDisks(current, opponent, possibleMoves[i]);
        // create possible moves vector for the opponent for the i'th move
        opponentMoves = gCopy.possibleMoves(opponent, current);
        xBefore = gCopy.getBoard()->numOfX();
        // go over the opponent's moves
        for (unsigned int j = 0; j < opponentMoves.size(); j++) {
            GameLogic gCopy1(gCopy);
            // turn the disks of the j'th move
            gCopy1.turnDisks(opponent, current, opponentMoves[j]);
            xAfter = gCopy1.getBoard()->numOfX();
            // if the j'th move increases the number of x's
            if (xAfter >= xBefore) {
            	// grade the move as the number of the added x's
                grade.push_back(xAfter - xBefore);
            } else {
            	// grade it as 0
                grade.push_back(0);
            }
        }
        if (!grade.empty()) {
            // push the max grade as this possible move's grade
            gradeFinal.push_back(getMax(grade));
            grade.clear();
       }
       grade.clear();
    }
    int bestMoveIndex = 0;
    // if there is more than one possible move
    if (!gradeFinal.empty()) {
        // get the best move's index (the one with the lowest grade)
        bestMoveIndex = getMinIndex(gradeFinal);
    }
    // return the move
    return possibleMoves[bestMoveIndex];
}

/**
 * function name: getGameLogic()
 * input: void
 * output: GameLogic
 * operation: returns const of the private gameLogic
 */
GameLogic *AIPlayer::getGameLogic() const {
    return gameLogic;
}


/**
 * function name: getGameLogicCopy()
 * input: void
 * output: GameLogic
 * operation: returns const of the private gameLogicCopy
 */
GameLogic *AIPlayer::getGameLogicCopy() const {
    return gameLogicCopy;
}

/**
 * function name: getMinIndex()
 * input: vector<int>
 * output: int
 * operation: returns the index of the minimum value of the vector, -1 if empty
 */
int AIPlayer::getMinIndex(vector<int> vec) {
	if (vec.empty()) {
		return -1;
	}
	int min = vec[0];
	int minIndex = 0;
	for (unsigned int i = 0; i < vec.size(); i++) {
		if (vec[i] < min) {
			min = vec[i];
			minIndex = i;
	    }
	}
	return minIndex;
}

/**
 * function name: getMax()
 * input: vector<int>
 * output: int
 * operation: returns the maximum value of the vector, -1 if empty
 */
int AIPlayer::getMax(vector<int> vec) {
	if (vec.empty()) {
		return -1;
	}
	int max = vec[0];
	// go over the vector
    for (unsigned int i = 0; i < vec.size(); i++) {
    	// update the max grade
        if (vec[i] > max) {
        	max = vec[i];
        }
    }
    return max;
}