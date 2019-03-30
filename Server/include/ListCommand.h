#ifndef EX4_SERVER_LISTCOMMAND_H
#define EX4_SERVER_LISTCOMMAND_H

#include "Command.h"

class ListCommand: public Command {
public:
    ListCommand(struct commandArgs* initArgs);
    bool execute(vector<string> args);

private:
    int socket;
    RoomsList* list;
};


#endif //EX4_SERVER_LISTCOMMAND_H
