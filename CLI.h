//* Author: 318509700 Peleg
//*         207984956 Nadav

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    DefaultIO *dio;
    vector<Command> commandsVector;
    // you can add data members
public:
    CLI(DefaultIO *dio);

    void start();

    virtual ~CLI();
};

#endif /* CLI_H_ */
