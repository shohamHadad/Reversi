#ifndef ADVANCEDPROGRAMMING1_COMMANDMANAGER_H
#define ADVANCEDPROGRAMMING1_COMMANDMANAGER_H


#include <map>
#include "Command.h"
#include "../include/StartCommand.h"
#include "../include/JoinCommand.h"
#include "../include/ListCommand.h"

using namespace std;

class CommandManager {
public:
    CommandManager(int socket);
    ~CommandManager();
    int executeCommand(string command, string name);
    vector<string> commandMenu();

private:
    map<string, Command*> commandsMap;
};


#endif //ADVANCEDPROGRAMMING1_COMMANDMANAGER_H
