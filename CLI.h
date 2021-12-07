//* Author: 318509700 Peleg
//*         207984956 Nadav

#ifndef CLI_H_
#define CLI_H_

#include <cstring>
#include "commands.h"

using namespace std;

 class CLI {
    DefaultIO *dio;
    vector<Command*> commandsVector;
    void buildCommandVector();
public:

    //public members
    TimeSeries ts;

    CLI(DefaultIO *dio) : dio(dio) {
        this->commandsVector = vector<Command>();
    }

    void start();

    virtual ~CLI();
};

#endif /* CLI_H_ */
