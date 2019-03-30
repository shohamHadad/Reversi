#ifndef EX4_SERVER_COMMAND_H
#define EX4_SERVER_COMMAND_H

#include <vector>
#include <string>
#include "RoomsList.h"

using namespace std;

struct commandArgs {
    int socket;
    RoomsList* list;
};

class Command {

public:
    virtual bool execute(vector<string> args) = 0;
    virtual ~Command() {}
};


#endif //EX4_SERVER_COMMAND_H
