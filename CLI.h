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
    HybridAnomalyDetector *hybridAnomalyDetector;
    vector<AnomalyReport> anomalyReportVec;
    float *correlation;

    void buildCommandVector();

public:
    CLI(DefaultIO *dio) : dio(dio) {
        this->hybridAnomalyDetector = new HybridAnomalyDetector();
        this->anomalyReportVec = vector<AnomalyReport>();
        this->correlation = &hybridAnomalyDetector->thresholdDetector;
        this->buildCommandVector();
    };

    void start();

    virtual ~CLI() {
        delete this->hybridAnomalyDetector;
        for (Command *command: this->commandsVector) {
            delete command;
        }
    };
};

#endif /* CLI_H_ */
