#include "StartCommand.h"


/**
 * function name: StartCommand
 * input: struct commandArgs
 * output: new object of StartCommand
 * operation: constructor
 */
StartCommand::StartCommand(struct commandArgs* initArgs): socket(initArgs->socket), list(initArgs->list) {}

/**
 * function name: execute
 * input: vector<string> args
 * output: void
 * operation: open a new room with the given name and add it to the list.
 */
bool StartCommand::execute(vector<string> args) {
    string name = args[0];
    if (list->contains(name)) {
        return inValidName(name);
    }
    Room* room = new Room(name);
    room->setClient1Socket(socket);
    room->setWaiting(true);
    list->addRoom(room);
    int order = 1;
    int n = write(socket, &order, sizeof(order));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return false;
    }
    return false;
}

/**
 * function name: inValidName
 * input: string name
 * output: bool
 * operation: send the client a message that his name choice is invalid.
 */
bool StartCommand::inValidName(string name) {
    stringstream message;
    message << endl << "the name '" << name << "' already exits. please choose a different name." << endl;
    int length = strlen(message.str().c_str());
    int n = write(socket, &length, sizeof(length));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return false;
    }
    n = write(socket, message.str().c_str(), length);
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return false;
    }
    return true;
}
