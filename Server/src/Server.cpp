#include "Server.h"

pthread_mutex_t rooms_locker;
pthread_mutex_t threads_locker;

using namespace std;

#define THREADS_NUM 5
#define MAX_CONNECTED_CLIENTS 50

/**
 * function name: Server()
 * input: int
 * output: Server
 * operation: constructor
 */
Server::Server(int port): port(port), serverThreadId(0), serverSocket(0), num_of_connections(0),
                          online(false) {
    rooms = new RoomsList();
    cout << "Welcome to Server" << endl;
    // Initialize mutex
    pthread_mutex_init(&rooms_locker, 0);
    pthread_mutex_init(&threads_locker, 0);
    // create the thread pool
    pool = new ThreadPool(THREADS_NUM);
}

/**
 * function name: start()
 * input: void
 * output: void
 * operation: activate the server
 */
void Server::start() {
    // Create a socket point
    serverSocket= socket(AF_INET, SOCK_STREAM,0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void*)&serverAddress,sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *)& serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    online = true;

    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    pthread_create(&serverThreadId, NULL, &acceptClients, (void*)this);
}


/**
 * function name: acceptClients
 * input: void* element
 * output: void
 * operation: Accept new client connections
 */
void* acceptClients(void* element) {
    Server* server = (Server*) element;

    // While server is online
    while (server->isOnline()) {
        cout << "Waiting for client connections..." << endl;
        // Accepted a client
        struct sockaddr_in clientAdress;
        socklen_t clientAdressLen = sizeof((struct sockadrr *) &clientAdress);
        int clientSocket = accept(server->getServerSocket(), (struct sockaddr *)&clientAdress,
                                  &clientAdressLen);
        if (clientSocket == -1) {
            throw "Error on accept";
        }

        struct commandArgs* args = new commandArgs;
        args->socket = clientSocket;
        args->list = server->getRooms();

        server->getPool()->addTask(new Task(HandleClient::handle, (void*)args));
    }
}

/**
 * function name: stop
 * input: void
 * output: void
 * operation: closes the server
 */
void Server::stop() {
    online = false;
    pool->terminate();
    pthread_cancel(serverThreadId);
    close(serverSocket);
    cout << "Server stopped" << endl;
}
/**
 * function name: ~Server
 * input: void
 * output: void
 * operation: destructor
 */
Server::~Server() {
    delete rooms;
    pthread_mutex_destroy(&threads_locker);
    pthread_mutex_destroy(&rooms_locker);
    delete pool;
}

/**
 * function name: isOnline
 * input: void
 * output: bool
 * operation: return the private bool online
 */
bool Server::isOnline() {
    return online;
}

/**
 * function name: getServerSocket
 * input: void
 * output: int
 * operation: return the private int serverSocket
 */
int Server::getServerSocket() const {
    return serverSocket;
}

/**
 * function name: getRooms
 * input: void
 * output: RoomsList*
 * operation: return the rooms list
 */RoomsList* Server::getRooms() const {
    return rooms;
}


ThreadPool* Server::getPool() {
    return pool;
}
