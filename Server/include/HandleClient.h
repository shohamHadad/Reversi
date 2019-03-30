#ifndef EX4_SERVER_HANDLECLIENT_H
#define EX4_SERVER_HANDLECLIENT_H

#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <strstream>
#include <vector>
#include "RoomsList.h"
#include "CommandsManager.h"
#include <sstream>

using namespace std;

class HandleClient {
public:
    static void* handle(void*);
    static vector<string> readMessage(int clientSocket);
    static bool nonValidRead(int n);
    static vector<string> buildMessage(int clientSocket, int numOfLetters);
};

#endif //EX4_SERVER_HANDLECLIENT_H
