#include"../server/Server.h"
#include <fstream>

using namespace std;

int readPortFromFile();

int main() {
    Server* server = new Server(readPortFromFile());
    try {
        server->start();
        string str;
        while (str != "exit") {
            cout << "Enter exit to stop server" << endl;
            cin >> str;
            if (str == "exit") {
                server->stop();
            }
        }
    }
    catch(const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        delete server;
        exit(-1);
    }
    delete server;
}

/**
 * function name: readPortFromFile
 * input: void
 * output: int
 * operation: read the port number from the given file and returns it
 */
int readPortFromFile() {
    ifstream inFile;
    string s;
    inFile.open("../client settings.txt");
    inFile >> s;
    // parse the port from string to int
    int port = atoi(s.c_str());
    inFile.close();
    return port;
}