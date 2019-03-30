#include "JoinCommand.h"
/**
 * function name: JoinCommand
 * input: struct commandArgs
 * output: new object of JoinCommand
 * operation: constructor
 */
JoinCommand::JoinCommand(struct commandArgs* initArgs): socket(initArgs->socket), list(initArgs->list) {}

/**
 * function name: execute
 * input: vector<string> args
 * output: bool
 * operation: add the client's socket to the given room, play the game and close the room
 */
bool JoinCommand::execute(vector<string> args) {
    string name = args[0];
    //check if the room exists
    if (!list->contains(name) || !list->getRoom(name)->isWaiting()) {
        return inValidChoice(name);
    }
    
    // add the client to the room, play the game and close the room
    Room* r = list->getRoom(name);
    r->addSecondClient(socket);
    RoomManager* manager = new RoomManager(r);
    manager->play();
    manager->closeRoom(list);
    return false;
}

/**
 * function name: inValidChoice
 * input: string name
 * output: void
 * operation: send the client a message that his choice was invalid.
 */
bool JoinCommand::inValidChoice(string name) {
    stringstream message;
    message << endl << "the game '" << name << "' isn't available. please choose a different game." << endl;
    string s = message.str();
    int length = strlen(s.c_str());
    int n = write(socket, &length, sizeof(length));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return false;
    }
    n = write(socket, s.c_str(), length);
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return false;
    }
    return true;
}
