#ifndef CLIENTPLAYER_H_
#define CLIENTPLAYER_H_

#include "Client.h"
#include "Player.h"
#include "Square.h"
#include <limits>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>

class ClientPlayer: public Client,  public Player {
public:
	ClientPlayer(const char *serverIP, int serverPort);
	void sendNextMove(int x, int y);
	Square chooseSquare(vector<Square>, Player*, Player*);
	void printPossibleMoves(vector <Square> moves);
	void waitForOtherPlayer();
    Square getNextMove();
    void noMove(Player*, Player*);
	void endGame();
    virtual ~ClientPlayer();
};

#endif /* CLIENTPLAYER_H_ */
