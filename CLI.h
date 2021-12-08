//* Author: 318509700 Peleg
//*         207984956 Nadav

#ifndef CLI_H_
#define CLI_H_

#include <cstring>
#include "commands.h"
#include "UploadCommand.h"
#include "HybridAnomalyDetector.h"

using namespace std;

 class CLI {
    DefaultIO *dio;
    vector<Command*> commandsVector;
    float correlation;
    HybridAnomalyDetector* hybridAnomalyDetector;
    vector<AnomalyReport> anomalyReportVec;

    void buildCommandVector();
public:
    CLI(DefaultIO *dio) : dio(dio) {
        this->correlation = 0.9;
        this->hybridAnomalyDetector =  new HybridAnomalyDetector();
        this->anomalyReportVec =  vector<AnomalyReport>();
        this->buildCommandVector();
    };

    void start();

    virtual ~CLI(){
    };
};

#endif /* CLI_H_ */
