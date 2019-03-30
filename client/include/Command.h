#ifndef ADVANCEDPROGRAMMING1_COMMAND_H
#define ADVANCEDPROGRAMMING1_COMMAND_H

#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <sstream>

using namespace std;
class Command {

public:
    Command(int socket);
    virtual int execute(string name) = 0;
    void writeCommand(char* commandName, string name);
    int executeFeedback(int order);
    bool nonValidRead(int n) const;
    virtual ~Command() {}

private:
    int socket;
};

#endif //ADVANCEDPROGRAMMING1_COMMAND_H
