#include "../include/Command.h"



/**
 * function name: Command
 * input: int socket
 * output: new object of Command
 * operation: constructor
 */
Command::Command(int socket): socket(socket){}

/**
 * function name: writeCommand
 * input: char*, string
 * output: void
 * operation: writes the command to the socket
 */
void Command::writeCommand(char* commandName, string name) {
    // writing commandName to socket
    int numOfLetters = strlen(commandName);
    int n = write(socket, &numOfLetters, sizeof(numOfLetters));
    if (n == -1) {
        throw "Error writing command's length to socket";
    }
    n =  write(socket, commandName, numOfLetters);
    if (n == -1) {
        throw "Error writing command's name to socket";
    }

    // writing name to socket
    numOfLetters = strlen(name.c_str());
    n = write(socket, &numOfLetters, sizeof(numOfLetters));
    if (n == -1) {
        throw "Error writing command's argument's length to socket";
    }
    n =  write(socket, name.c_str(), numOfLetters);
    if (n == -1) {
        throw "Error writing command's argument to socket";
    }
}


/**
 * function name: nonValidRead
 * input: n
 * output: true or false
 * operation: validates the reading returned value
 */
bool Command::nonValidRead(int n) const {
    if (n == -1) {
        cout << "Error reading message" << endl;
        return true;
    } else if (n == 0) {
        cout << "Client disconnected" << endl;
        return true;
    };
    return false;
}

/**
 * function name: executeFeedback
 * input: int order
 * output: int
 * operation: read server's answer to the command. returns the order if the server executed the command.
 *            if it didn't, print the message that explains why and return -1.
 */
int Command::executeFeedback(int order) {
    // reading server's message
    int numOfLetters;
    int n = read(socket, &numOfLetters, sizeof(numOfLetters));
    if (n == -1) {
        throw "Error reading from socket";
    }
    // if the message is order, it means everything worked.
    if (numOfLetters == order) {
        return order;
    }
    // if the message isn't the order it means we have to read on
    stringstream messageBuilder;
    for (int i = 0; i < numOfLetters; i++) {
        char c;
        int n = read(socket, &c, sizeof(c));
        if (nonValidRead(n)) { return -1; }
        messageBuilder << c;
    }
    string message = messageBuilder.str();
    // print it to the user and return -1
    cout << message << endl;
    return -1;
}
