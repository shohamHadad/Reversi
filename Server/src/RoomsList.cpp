#include <sstream>
#include "RoomsList.h"

pthread_mutex_t roomsLocker;

/**
 * function name: RoomsList
 * input: void
 * output: new object of RoomsList
 * operation: constructor
 */
RoomsList::RoomsList() {
    pthread_mutex_init(&roomsLocker, 0);
}



/**
 * function name: getAvailableRooms
 * input: void
 * output: string
 * operation: returns a list of available game rooms.
 */
string RoomsList::getAvailableRooms() {
    pthread_mutex_trylock(&roomsLocker);
    // if there are no rooms in the list
    if (rooms.empty()) {
        pthread_mutex_unlock(&roomsLocker);
        stringstream message;
        message << endl << "There aren't any available games to display" << endl;
        return message.str();
    }
    // make a string out of the waiting rooms in the list
    stringstream builder;
    builder << "Available Games:" << endl;
    int j = 1;
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->isWaiting()) {
            builder << j << ". " << rooms[i]->getName() << endl;
            j++;
        }
    }
    pthread_mutex_unlock(&roomsLocker);
    return builder.str();
}

/**
 * function name: contains
 * input: string roomName
 * output: bool
 * operation: returns true if the room's name is in the list, otherwise false
 */
bool RoomsList::contains(string roomName) {
    pthread_mutex_trylock(&roomsLocker);
    if (rooms.empty()) {
        pthread_mutex_unlock(&roomsLocker);
        return false;
    }
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getName() == roomName) {
            return true;
        }
    }
    pthread_mutex_unlock(&roomsLocker);
    return false;
}


/**
 * function name: getRoom
 * input: string roomName
 * output: Room
 * operation: returns the room to which the player wants to connect.
 */
Room* RoomsList::getRoom(string roomName) const {
    pthread_mutex_trylock(&roomsLocker);
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getName() == roomName) {
            Room* r = rooms[i];
            pthread_mutex_unlock(&roomsLocker);
            return r;
        }
    }
}


/**
 * function name: removeRoom
 * input: string roomName
 * output: void
 * operation: delete the given room from the list.
 */
void RoomsList::removeRoom(string roomName) {
    pthread_mutex_trylock(&roomsLocker);
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getName() == roomName) {
            delete rooms[i];
            rooms.erase(rooms.begin() + i);
            pthread_mutex_unlock(&roomsLocker);
            return;
        }
    }
}

/**
 * function name: addRoom
 * input: Room* r
 * output: void
 * operation: add the given room to the list.
 */
void RoomsList::addRoom(Room* r) {
    pthread_mutex_trylock(&roomsLocker);
    rooms.push_back(r);
    pthread_mutex_unlock(&roomsLocker);
}