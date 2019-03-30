#ifndef AIPLAYER_H_
#define AIPLAYER_H_
#include "Player.h"
#include "GameLogic.h"
#include "Square.h"
#include <iostream>
using namespace std;

class AIPlayer : public Player {
private:
	GameLogic* gameLogic;
	GameLogic *gameLogicCopy;

public:
	AIPlayer(char ,GameLogic*);
	virtual ~AIPlayer();
	Square chooseSquare(vector<Square>, Player*, Player*);
	GameLogic *getGameLogic() const;
	GameLogic *getGameLogicCopy() const;
	int getMinIndex(vector<int>);
	int getMax(vector<int>);
};

#endif /* AIPLAYER_H_ */
