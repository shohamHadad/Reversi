#ifndef EX4_SERVER_COMMANDSMANAGER_H
#define EX4_SERVER_COMMANDSMANAGER_H

#include <map>
#include "Command.h"
#include "RoomsList.h"
#include "StartCommand.h"
#include "JoinCommand.h"
#include "ListCommand.h"

class CommandsManager {
public:
    CommandsManager(struct commandArgs* initArgs);
    ~CommandsManager();
    bool executeCommand(string command, vector<string> args);

private:
    map<string, Command*> commandsMap;
};



#endif //EX4_SERVER_COMMANDSMANAGER_H
