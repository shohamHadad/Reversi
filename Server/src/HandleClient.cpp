#include "HandleClient.h"
using namespace std;

/**
 * function name: handleClient
 * input: int, int
 * output: void*
 * operation: read clients commands and send them to execution
 */
void* HandleClient::handle(void* arguents) {
    struct commandArgs* args = (struct commandArgs*)arguents;
    int clientSocket = args->socket;
    bool continueHandling = true;
    while (continueHandling) {
        // reading the letters' number of comming command
        int numOfLetters;
        int n = read(clientSocket, &numOfLetters, sizeof(numOfLetters));
        if (nonValidRead(n)) { return (void *) n; }
        // reading command's name
        stringstream stringBuilder;
        for (int i = 0; i < numOfLetters; i++) {
            char c;
            int n = read(clientSocket, &c, sizeof(c));
            if (nonValidRead(n)) { return (void*) n; }
            stringBuilder << c;
        }
        string command = stringBuilder.str();
        // reading the command's arguments
        vector<string> arg = readMessage(clientSocket);
        // calling a command manager to execute the command
        CommandsManager* cm = new CommandsManager(args);
        continueHandling = cm->executeCommand(command, arg);
        delete cm;
    }
    delete args;
}

/**
 * function name: readMessage
 * input: int
 * output: vector <string>
 * operation: Read the client's message and return it
 */
vector<string> HandleClient::readMessage(int clientSocket) {
    int numOfLetters;
    vector<string> message;
    // read the number
    int n = read(clientSocket, &numOfLetters, sizeof(numOfLetters));
    if (nonValidRead(n)) {return message; }
    message = buildMessage(clientSocket, numOfLetters);
    return message;
}

/**
 * function name: buildMessage
 * input: int, int
 * output: vector<string>
 * operation: read the client's message and returns it as a vector of strings
 */
vector<string> HandleClient::buildMessage(int clientSocket, int numOfLetters) {
    vector<string> msg;
    stringstream messageBuilder;
    if (numOfLetters < 0) {
        messageBuilder << numOfLetters;
        string str = messageBuilder.str();
        msg.push_back(str);
        return msg;
    }
    for (int i = 0; i < numOfLetters; i++) {
        char c;
        int n = read(clientSocket, &c, sizeof(c));
        if (nonValidRead(n)) { return msg; }
        if (c == ' ') {
            // push the string to the vector and clear the stream
            string str = messageBuilder.str();
            msg.push_back(str);
            messageBuilder.str("");
        } else {
            messageBuilder << c;
        }
    }
    string str = messageBuilder.str();
    msg.push_back(str);
    return msg;
}

/**
 * function name: nonValidRead
 * input: n
 * output: true or false
 * operation: validates the reading returned value
 */
bool HandleClient::nonValidRead(int n) {
    if (n == -1) {
        cout << "Error reading message" << endl;
        return true;
    } else if (n == 0) {
        cout << "Client disconnected" << endl;
        return true;
    };
    return false;
}