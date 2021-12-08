//* Author: 318509700 Peleg
//*         207984956 Nadav
#include "UploadCommand.h"



 void UploadCommand::execute(){
    cout<<"Please upload your local train CSV file."<<endl;
    string inputRead;
    // get the train csv from the user
    inputRead = this->getDefaultIO()->read()+",anomalyTrain.csv";
    this->getDefaultIO()->write(inputRead);
    cout<<"Upload complete."<<endl;

    // for the test file
     cout<<"Please upload your local test CSV file." <<endl;
     // get the input from the user
     inputRead = this->getDefaultIO()->read()+",anomalyTest.csv";
     this->getDefaultIO()->write(inputRead);
     cout<<"Upload complete."<<endl;
}

void correlCommand::execute() {
    cout<<"The current correlation threshold is " << + *this->correlation <<endl;
    string intput = this->getDefaultIO()->read();
    float numInput = stof(&intput[0]);
    //if the input is not 0-1 the user need to enter again
    while (1 < numInput || 0 > numInput){
        cout <<"please choose a value between 0 and 1." << endl;
        intput = this->getDefaultIO()->read();
        numInput = atoi(&intput[0]);
    }
    *this->correlation = numInput;
    //cout<<"The current correlation threshold is " << + *this->correlation <<endl;

}

void HybridCommand::execute() {
    TimeSeries tsTrain = TimeSeries("anomalyTrain.csv");
    this->ptrHybrid->learnNormal(tsTrain);
    TimeSeries tsTest = TimeSeries("anomalyTest.csv");
    *this->anomalyVec = this->ptrHybrid->detect(tsTest);
    cout<<"anomaly detection complete" <<endl;
}

void anomalyCommand::execute() {
    for(const AnomalyReport& report: *this->anomalyVec){
        int row = report.timeStep;
        cout << row <<  "\t" +report.description<< endl;
    }
    cout<< "Done." <<endl;

}
