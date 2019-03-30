#ifndef EX4_SERVER_JOINCOMMAND_H
#define EX4_SERVER_JOINCOMMAND_H

#include "Command.h"
#include "RoomManager.h"
#include <unistd.h>
#include <sstream>
#include <cstdlib>
#include <iostream>

class JoinCommand: public Command {

public:
    JoinCommand(struct commandArgs* initArgs);
    bool execute(vector<string> args);
    bool inValidChoice(string name);

private:
    int socket;
    RoomsList* list;
};

#endif //EX4_SERVER_JOINCOMMAND_H
