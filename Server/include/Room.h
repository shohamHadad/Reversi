#ifndef EX4_SERVER_ROOM_H
#define EX4_SERVER_ROOM_H

#include <string>

using namespace std;

class Room {

private:
    bool waiting;
    string name;
    int client1Socket;
    int client2Socket;

public:
    Room(string name);
    bool isWaiting() const;
    void setWaiting(bool b);
    const string &getName() const;
    int getClient1Socket() const;
    void setClient1Socket(int client1Socket);
    int getClient2Socket() const;
    void setClient2Socket(int client2Socket);
    void addSecondClient(int client2Socket);
};


#endif //EX4_SERVER_ROOM_H
