//* Author: 318509700 Peleg
//*         207984956 Nadav

#ifndef SIMPLE_EXAMPLE_UPLOADCOMMAND_H
#define SIMPLE_EXAMPLE_UPLOADCOMMAND_H


#include <utility>

#include "commands.h"
#include "HybridAnomalyDetector.h"
#include "timeseries.h"

class UploadCommand : public Command
        {
    //const string description = "upload a time series csv file";
public:

    //constructor
    UploadCommand(DefaultIO *dio) :
    Command(dio,"upload a time series csv file") {
    };

    virtual void execute();

};
///need check if there is need to new file
class correlCommand :public Command{
    float*  correlation;
public:
    correlCommand(DefaultIO *dio, float*  cor) :
    Command(dio,"algorithm settings") {
        this->correlation = cor;
    };
    virtual void execute();
};



class HybridCommand : public Command
{
public:
    HybridAnomalyDetector* ptrHybrid;
    vector<AnomalyReport>* anomalyVec;
    //constructor
    HybridCommand(DefaultIO *dio, HybridAnomalyDetector* ptr,vector<AnomalyReport> *ptrAnomaly) :
            Command(dio,"detect anomalies") {
        this->ptrHybrid= ptr;
        anomalyVec = ptrAnomaly;
    };

    virtual void execute();

};


class anomalyCommand : public Command
{
public:
    HybridAnomalyDetector* ptrHybrid;
    vector<AnomalyReport> *anomalyVec;
    //constructor
    anomalyCommand(DefaultIO *dio, HybridAnomalyDetector *ptr,  vector< AnomalyReport>* pVector) :
            Command(dio,"display results") {
        this->ptrHybrid= ptr;
        this->anomalyVec = pVector;
    };

    virtual void execute();

};

class resultCommand : public Command
{
public:
    HybridAnomalyDetector* ptrHybrid;
    vector<AnomalyReport> *anomalyVec;
    //constructor
    resultCommand(DefaultIO *dio, HybridAnomalyDetector *ptr,  vector< AnomalyReport>* pVector) :
            Command(dio,"upload anomalies and analyze results") {
        this->ptrHybrid= ptr;
        this->anomalyVec = pVector;
    };

    vector<pair<int,int>> inputAnomaly();


        virtual void execute();

};
#endif //SIMPLE_EXAMPLE_UPLOADCOMMAND_H
