#include "../include/StartCommand.h"

/**
 * function name:StartCommand
 * input: int socket
 * output: new object of StartCommand
 * operation: constructor
 */
StartCommand:: StartCommand(int socket): Command(socket) {}


/**
 * function name: execute
 * input: string name
 * output: int
 * operation: send the server a start command with the name of the game and execut the server's feedback
 */
int StartCommand::execute(string name) {
    writeCommand("start", name);
    return executeFeedback(1);
}
