
#include "../include/CommandManager.h"

/**
 * function name: CommandsManager
 * input: int
 * output: CommandManager
 * operation: constructor
 */
CommandManager::CommandManager(int socket){
    commandsMap["start"] = new StartCommand(socket);
    commandsMap["join"] = new JoinCommand(socket);
    commandsMap["list_games"] = new ListCommand(socket);
}

/**
 * function name: executeCommand
 * input: string command, string name
 * output: int
 * operation: execute the given command using the private map
 */
int CommandManager::executeCommand(string command, string name) {
    Command* commandObj = commandsMap[command];
    return commandObj->execute(name);
}

/**
 * function name: ~CommandsManager
 * input: void
 * output: void
 * operation: destructor
 */
CommandManager::~CommandManager() {
    map<string, Command*>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}

/**
 * function name: CommandMenu
 * input: void
 * output: vector<string>
 * operation: get the user's desired command and returns it
 */
vector<string> CommandManager::commandMenu() {
    // get the command type from the user
    int choice = 0;
    do {
        cout << "Please enter your choice:" << endl;
        cout << "   1 to start a new game" << endl;
        cout << "   2 to join an existing game" << endl;
        cout << "   3 to see the list of available games" << endl;
        cin >> choice;
    } while (choice < 1 || choice > 3);
    // match command to choice
    string command;
    vector<string> userInput;
    switch (choice) {
        case 1:
            command = "start";
            break;
        case 2:
            command = "join";
            break;
        case 3:
            command = "list_games";
        default:
            break;
    }
    string name = " ";

    // if user didn't choose to see the list, we need to take name
    if (command != "list_games") {
        // get the game's name from user and return the input
        cout << "Please enter your game's name: ";
        cin >> name;
    }
    userInput.push_back(command);
    userInput.push_back(name);
    return userInput;
}
