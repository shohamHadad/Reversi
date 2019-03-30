#include "../include/JoinCommand.h"

/**
 * function name: JoinCommand
 * input: int
 * output: new object of JoinCommand
 * operation: constructor
 */
JoinCommand::JoinCommand(int socket): Command(socket) {}

/**
 * function name: execute
 * input: string name
 * output: int
 * operation: send a join command to server with the name of the game to join, and execute the server's feedback
 */
int JoinCommand::execute(string name) {
    writeCommand("join", name);
    return executeFeedback(2);
}
