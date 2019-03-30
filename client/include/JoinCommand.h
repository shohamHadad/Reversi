#ifndef ADVANCEDPROGRAMMING1_JOINCOMMAND_H
#define ADVANCEDPROGRAMMING1_JOINCOMMAND_H

#include "Command.h"
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <sstream>

using namespace std;

class JoinCommand: public Command {

public:
    JoinCommand(int scoket);
    int execute(string name);
};


#endif //ADVANCEDPROGRAMMING1_JOINCOMMAND_H
