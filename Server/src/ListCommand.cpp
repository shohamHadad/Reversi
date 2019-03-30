#include <cstring>
#include <unistd.h>
#include <iostream>
#include "ListCommand.h"

/**
 * function name: ListCommand
 * input: struct commandArgs
 * output: new object of ListCommand
 * operation: constructor
 */
ListCommand::ListCommand(struct commandArgs* initArgs) : socket(initArgs->socket), list(initArgs->list) {}

/**
 * function name: execute
 * input: vector<string> args
 * output: bool
 * operation: send the client the list of waiting rooms
 */
bool ListCommand::execute(vector<string> args) {
    // get a list of available rooms
    string waitingRooms = list->getAvailableRooms();

    // send the list's length
    int numOfLetters = strlen(waitingRooms.c_str());
    int n = write(socket, &numOfLetters, sizeof(numOfLetters));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return false;
    }

    // send the list
    n = write(socket, waitingRooms.c_str(), numOfLetters);
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return false;
    }
    return true;
}