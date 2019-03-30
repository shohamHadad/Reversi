#include "RoomManager.h"

/**
 * function name: RoomManager
 * input: Room* room
 * output: a new object of RoomManager
 * operation: constructor
 */
RoomManager::RoomManager(Room* room): room(room) {
    client1Socket = room->getClient1Socket();
    client2Socket = room->getClient2Socket();
    turns = 0;
}

/**
 * function name: play
 * input: void
 * output: void
 * operation: run the game according to the possibole moves of the players.
 *            returns when a message of "-1" is recieved
 */
void RoomManager::play() {
    while(true) {
        vector<string> result;
        if (whosTurn(client1Socket, client2Socket) == client1Socket) {
            result = HandleClient::readMessage(client1Socket);
            if (result.empty()) {return;}
            if(result[0] == "-1") {
                cout << "End Game" << endl;
                return;
            }
            else if(result[0] == "-2") {
                cout << "No Move" << endl;
            } else {
                sendMove(result, client2Socket);
            }
        } else {
            result = HandleClient::readMessage(client2Socket);
            if(result[0] == "-1") {
                cout << "End Game" << endl;
                return;
            }
            else if(result[0] == "-2") {
                cout << "No Move" << endl;
            } else {
                sendMove(result, client1Socket);
            }
        }
        turns++;
    }
}

/**
 * function name: sendMove
 * input: vector<string>, int
 * output: void
 * operation: write the given move to the given socket
 */
void RoomManager::sendMove(vector<string> move, int toClientSocket) const {
    // Write x to the client
    int x = atoi(move[0].c_str());
    int n = write(toClientSocket, &x, sizeof(x));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return;
    }
    // Write y to the client
    int y = atoi(move[1].c_str());
    n = write(toClientSocket, &y, sizeof(y));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
        return;
    }
}

/**
 * function name: whosTurn
 * input: int, int
 * output: int
 * operation: returns the clientSocket who's turn it is
 */
int RoomManager::whosTurn(int first, int second) {
    if (turns % 2 == 0) {
        return first;
    }
    return second;
}

/**
 * function name: closeRoom
 * input: RoomsList* list
 * output: void
 * operation: close the room's sockets and remove it from the given rooms list.
 */
void RoomManager::closeRoom(RoomsList* list) {
    // close it's two sockets
    close(room->getClient1Socket());
    close(room->getClient2Socket());
    list->removeRoom(room->getName());
}
