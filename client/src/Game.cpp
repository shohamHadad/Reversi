#include "../include/Game.h"

/**
 * function name: Game
 * input: void
 * output: new game object
 * operation: constructor
 */
Game::Game() {
	logic = new GameLogic(new Board(4));
    settingDataFlag = false;
}

/**
 * function name: ~Game
 * input: void
 * output: void
 * operation: destructor
 */
Game::~Game() {
	delete logic;
	delete X;
	delete O;
    if (settingDataFlag) {
        delete sd;
    }
}

/**
 * function name: initialize
 * input: void
 * output: void
 * operation: get the user's chosen opponent and initialize the game with it
 */
void Game::initialize() {
	cout << "Welcome to Reversi!" << endl << "Choose an opponent type:"	<< endl	<<
			"	1. a human local player" << endl <<
		 	"	2. an AI player" << endl <<
		 	"	3. a remote player"	<< endl;
	int choice;
	cin >> choice;
	while (choice != 1 && choice != 2 && choice != 3) {
		cout << "Please choose 1, 2 or 3" << endl;
		cin >> choice;
	}
	switch (choice) {
	case 1:
		X = new HumanPlayer('X');
		O = new HumanPlayer('O');
		break;
	case 2:
		X = new HumanPlayer('X');
		O = new AIPlayer('O', logic);
		break;
	case 3:
        sd = new SettingData();
        settingDataFlag = true;
        assignClientAndRemotePlayers(sd);
        break;
	default:
		break;
	}
}


/**
 * function name: play
 * input: void
 * output: void
 * operation: activates the game loop
 */
void Game::play() {
    logic->printBoard();
	while (!logic->gameShouldStop(X, O)) {
		Player* current;
		Player* opponent;
		if (logic->whosTurn(X,O)->equals(X)) {
			current = X;
			opponent = O;
		} else {
			current = O;
			opponent = X;
		}
		logic->playOneTurn(current, opponent);
	}
	logic->endGame(X, O);
}


/**
 * function name: assignClientAndRemotePlayers
 * input: SettingData* sd
 * output: void
 * operation: get the user's command, and according to it and to the given SettingData creates
 *            ClientPlayer and RemotePlayer
 */
void Game::assignClientAndRemotePlayers(SettingData* sd) {
	try {
		ClientPlayer* cp = new ClientPlayer(sd->getIP(), sd->getPort());
		RemotePlayer* rp = new RemotePlayer();
		cp->connectToServer();
		CommandManager* manager = new CommandManager(cp->getClientSocket());
		int order = -1;
		while (order == -1) {
			vector<string> command = manager->commandMenu();
			order = manager->executeCommand(command[0], command[1]);
		}
		if (order == 1) {
			X = cp;
			O = rp;
            cp->waitForOtherPlayer();
		} else {
			O = cp;
			X = rp;
		}
		X->setType('X');
		O->setType('O');
		delete manager;
    } catch (const char *msg) {
		cout << "Failed to connect to server. Reason: " << msg << endl;
		exit(-1);
	}
}
