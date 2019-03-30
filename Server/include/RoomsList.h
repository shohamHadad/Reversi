#ifndef EX4_SERVER_ROOMSLIST_H
#define EX4_SERVER_ROOMSLIST_H

#include <string>
#include <vector>
#include "Room.h"

using namespace std;

class RoomsList {
private:
    vector<Room*> rooms;

public:
    RoomsList();
    string getAvailableRooms();
    bool contains(string roomName);
    Room* getRoom(string roomName) const;
    void removeRoom(string roomName);
    void addRoom(Room* r);
};


#endif //EX4_SERVER_ROOMSLIST_H
