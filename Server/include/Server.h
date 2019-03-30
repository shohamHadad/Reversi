#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <strstream>
#include <vector>
#include <list>
#include "RoomsList.h"
#include "HandleClient.h"
#include "ThreadPool.h"
#include <arpa/inet.h>
#include <sstream>
#include <stdexcept>
#include <pthread.h>

using namespace std;

class Server {

private:
    pthread_t serverThreadId;
    int serverSocket;
    RoomsList* rooms;
    int port;
    int num_of_connections;
    bool online;
    ThreadPool* pool;

public:
    Server(int port);
    ~Server();
    void start();
    bool isOnline();
    void stop();
    vector<pthread_t> &getThreads();
    int getServerSocket() const;
    RoomsList *getRooms() const;
    ThreadPool* getPool();
};

struct ClientData {
    int clientSocket;
    Server* server;
};

static void* acceptClients(void* element);

#endif //SERVER_H