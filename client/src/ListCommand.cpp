#include "../include/ListCommand.h"

/**
 * function name: ListCommand
 * input: int
 * output: new object of ListCommand
 * operation: constructor
 */
ListCommand::ListCommand(int socket): Command(socket) {}

/**
 * function name: execute
 * input: string name
 * output: int
 * operation: send a list command to the server and execute the server's feedback
 */
int ListCommand::execute(string name) {
    writeCommand("list_games", name);
    return executeFeedback(-1);
}
