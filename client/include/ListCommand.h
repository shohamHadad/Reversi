#ifndef ADVANCEDPROGRAMMING1_LISTCOMMAND_H
#define ADVANCEDPROGRAMMING1_LISTCOMMAND_H

#include "Command.h"
using namespace std;

class ListCommand: public Command {

public:
    ListCommand(int scoket);
    int execute(string name);
};

#endif //ADVANCEDPROGRAMMING1_LISTCOMMAND_H
