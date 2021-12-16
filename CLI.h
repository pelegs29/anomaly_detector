//* Author: 318509700 Peleg
//*         207984956 Nadav

#ifndef CLI_H_
#define CLI_H_

#include <cstring>
#include "commands.h"
#include "HybridAnomalyDetector.h"

using namespace std;

class CLI {
    DefaultIO *dio;
    vector<Command *> commandsVector;
    CLI_Data *data;

    void buildCommandVector();

public:
    CLI(DefaultIO *dio) : dio(dio) {
        this->data = new CLI_Data();
        this->buildCommandVector();
    };

    void start();

    virtual ~CLI();
};


#endif /* CLI_H_ */
