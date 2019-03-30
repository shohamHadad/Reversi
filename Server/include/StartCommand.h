#ifndef EX4_SERVER_STARTCOMMAND_H
#define EX4_SERVER_STARTCOMMAND_H
#include <unistd.h>
#include <sstream>
#include <cstring>
#include "Command.h"
#include <iostream>

class StartCommand: public Command {

public:
    StartCommand(struct commandArgs* initArgs);
    bool execute(vector<string> args);
    bool inValidName(string name);

private:
    int socket;
    RoomsList* list;
};


#endif //EX4_SERVER_STARTCOMMAND_H
