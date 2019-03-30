#ifndef EX4_SERVER_ROOMMANAGER_H
#define EX4_SERVER_ROOMMANAGER_H

#include <string>
#include <vector>
#include "RoomsList.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "Server.h"

using namespace std;

class RoomManager {

private:
    Room* room;
    int client1Socket;
    int client2Socket;
    int turns;

public:
    RoomManager(Room* room);
    void play();
    void sendMove(vector<string> message, int toClientSocket)const;
    int whosTurn(int client1Socket, int client2Socket);
    void closeRoom(RoomsList* list);
};


#endif //EX4_SERVER_ROOMMANAGER_H
