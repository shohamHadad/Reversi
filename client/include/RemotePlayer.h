#ifndef REMOTEPLAYER_H_
#define REMOTEPLAYER_H_

#include "Player.h"
#include "Client.h"
#include "Square.h"
#include <iostream>

class RemotePlayer: public Player {
public:
	RemotePlayer();
	Square chooseSquare(vector<Square>, Player*, Player*);
	virtual ~RemotePlayer();
    void waitForOtherPlayerMove();
};

#endif /* REMOTEPLAYER_H_ */
