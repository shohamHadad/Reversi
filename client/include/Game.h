#ifndef GAME_H_
#define GAME_H_
#include "GameLogic.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "ClientPlayer.h"
#include "RemotePlayer.h"
#include "SettingData.h"
#include "stdlib.h"
#include <iostream>
#include <limits>
#include "../include/CommandManager.h"
using namespace std;


/**
 * the game can be played.
 */
class Game {
private:
	GameLogic* logic;
	Player* X;
	Player* O;
	SettingData* sd;
	bool settingDataFlag;

public:
	Game();
	virtual ~Game();
	void play();
	void initialize();
	void assignClientAndRemotePlayers(SettingData*);
};

#endif /* GAME_H_ */
