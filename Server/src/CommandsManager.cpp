#include "CommandsManager.h"

/**
 * function name: CommandsManager
 * input: sturct commandArgs initArgs
 * output: new Command object
 * operation: constructor
 */
CommandsManager::CommandsManager(struct commandArgs* initArgs) {
    commandsMap["start"] = new StartCommand(initArgs);
    commandsMap["join"] = new JoinCommand(initArgs);
    commandsMap["list_games"] = new ListCommand(initArgs);
}

/**
 * function name: executeCommand
 * input: string command, vector <string> args
 * output: bool
 * operation: execute the given command according to the private map and returns true to continue
 *            recieving new commands and false to stop the communication with this socket.
 */
bool CommandsManager::executeCommand(string command, vector<string> args) {
    Command* commandObj = commandsMap[command];
    return commandObj->execute(args);
}

/**
 * function name: ~CommandsManager
 * input: void
 * output: void
 * operation: destructor
 */
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}
