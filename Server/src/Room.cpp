#include <unistd.h>
#include <iostream>
#include "Room.h"

/**
 * function name: Room
 * input: string name
 * output: new Room object
 * operation: constructor
 */
Room::Room(string name): name(name) {
}

/**
 * function name: isWaiting
 * input: void
 * output: bool
 * operation: return waiting
 */
bool Room::isWaiting() const {
    return waiting;
}


/**
 * function name: setWaiting
 * input: gets a bool b
 * output: void
 * operation: set waiting to be b.
 */
void Room::setWaiting(bool b) {
    waiting = b;
}


/**
 * function name: getName
 * input: void
 * output: string
 * operation: return the name of room
 */
const string &Room::getName() const {
    return name;
}

/**
 * function name: getClient1Socket
 * input: void
 * output: int
 * operation: return client1Socket
 */
int Room::getClient1Socket() const {
    return client1Socket;
}


/**
 * function name: setClient1Socket
 * input: int client1Socket
 * output: void
 * operation: set client1Socket to the given int
 */
void Room::setClient1Socket(int client1Socket) {
    Room::client1Socket = client1Socket;
}


/**
 * function name: getClient2Socket
 * input: void
 * output: int
 * operation: return client2Socket
*/
int Room::getClient2Socket() const {
    return client2Socket;
}

/**
 * function name: setClient2Socket
 * input: int client2Socket
 * output: void
 * operation: set client2Socket to be the given int
 */
void Room::setClient2Socket(int client2Socket) {
    Room::client2Socket = client2Socket;
}


/**
 * function name: addSecondClient
 * input: int socket2
 * output: void
 * operation: add the given socket to the room and notify the clients they can start the game
 */
void Room::addSecondClient(int socket2) {
    setClient2Socket(socket2);
    setWaiting(false);
    int order = 2;
    int n = write(socket2, &order, sizeof(order));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
    }
    // send client1 message that the game begins
    n = write(client1Socket, &order, sizeof(order));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
    }
}