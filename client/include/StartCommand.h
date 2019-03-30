#ifndef ADVANCEDPROGRAMMING1_STARTCOMMAND_H
#define ADVANCEDPROGRAMMING1_STARTCOMMAND_H

#include "Command.h"
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <iostream>

using namespace std;

class StartCommand: public Command {

public:
    StartCommand(int scoket);
    int execute(string name);
};

#endif //ADVANCEDPROGRAMMING1_STARTCOMMAND_H
