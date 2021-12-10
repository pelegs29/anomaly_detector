//* Author: 318509700 Peleg
//*         207984956 Nadav

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <utility>

#include "HybridAnomalyDetector.h"
#include "timeseries.h"

using namespace std;

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() = default;

    // you may add additional methods here
};

// you may edit this class
class Command {

    string description;
    DefaultIO *dio;

public:

    // constructor
    Command(DefaultIO *dioIn, string descIn) {
        //dio(dio), description(desc)
        description = descIn;
        dio = dioIn;
    }

    virtual void execute() = 0;

    virtual ~Command() = default;

    string getDesc() {
        return this->description;
    }

    DefaultIO *getDefaultIO() {
        return this->dio;
    }

    void readCSV(string text) {
        //vector<string> input = inputString(text);
        //string src = input[0];
        //string desName = input[1];
        // File input pointer
        ofstream outfile(text);
        //ifstream inputFile(src); // the file that I need to upload to the server
        // Open an existing file
        //if(!inputFile.is_open()) throw runtime_error("Could not open file");
        string line;
        while (true) {
            line = this->getDefaultIO()->read();
            if (line == "done") {
                break;
            }
            outfile << line + "\n";
        }
        outfile.close();
        //inputFile.close();
    }
};

class UploadCommand : public Command {
    //const string description = "upload a time series csv file";
public:

    //constructor
    explicit UploadCommand(DefaultIO *dio) :
            Command(dio, "upload a time series csv file") {
    };

    virtual void execute() override {
        this->getDefaultIO()->write("Please upload your local train CSV file.\n");
        string inputRead;
        // get the train csv from the user
        inputRead = "anomalyTrain.csv";
        this->readCSV(inputRead);
        this->getDefaultIO()->write("Upload complete.\n");

        // for the test file
        this->getDefaultIO()->write("Please upload your local test CSV file.\n");
        // get the input from the user
        inputRead = "anomalyTest.csv";
        this->readCSV(inputRead);
        this->getDefaultIO()->write("Upload complete.\n");
    }
};


///need check if there is need to new file
class correlCommand : public Command {
    float *correlation;
public:
    correlCommand(DefaultIO *dio, float *cor) :
            Command(dio, "algorithm settings") {
        this->correlation = cor;
    };

    virtual void execute() override {
        this->getDefaultIO()->write("The current correlation threshold is " + to_string(*this->correlation) + "\n");
        this->getDefaultIO()->write("Type a new threshold\n");
        string intput = this->getDefaultIO()->read();
        float numInput = stof(&intput[0]);
        //if the input is not 0-1 the user need to enter again
        while (1 < numInput || 0 > numInput) {
            this->getDefaultIO()->write("please choose a value between 0 and 1.\n");
            intput = this->getDefaultIO()->read();
            numInput = (float) stoi(&intput[0]);
        }
        *this->correlation = numInput;
    }
};


class HybridCommand : public Command {
public:
    HybridAnomalyDetector *ptrHybrid;
    vector<AnomalyReport> *anomalyVec;

    //constructor
    HybridCommand(DefaultIO *dio, HybridAnomalyDetector *ptr, vector<AnomalyReport> *ptrAnomaly) :
            Command(dio, "detect anomalies") {
        this->ptrHybrid = ptr;
        anomalyVec = ptrAnomaly;
    };

    virtual void execute() override {
        TimeSeries tsTrain = TimeSeries("anomalyTrain.csv");
        this->ptrHybrid->learnNormal(tsTrain);
        TimeSeries tsTest = TimeSeries("anomalyTest.csv");
        *this->anomalyVec = this->ptrHybrid->detect(tsTest);
        this->getDefaultIO()->write("anomaly detection complete.\n");
    }

};


class anomalyCommand : public Command {
public:
    vector<AnomalyReport> *anomalyVec;

    //constructor
    anomalyCommand(DefaultIO *dio, vector<AnomalyReport> *pVector) :
            Command(dio, "display results") {
        this->anomalyVec = pVector;
    };

    virtual void execute() override {
        for (const AnomalyReport &report: *this->anomalyVec) {
            int row = report.timeStep;
            this->getDefaultIO()->write(to_string(row) + "\t" + report.description + "\n");
        }
        this->getDefaultIO()->write("Done.\n");
    }

};

class resultCommand : public Command {
public:
    HybridAnomalyDetector *ptrHybrid;
    vector<AnomalyReport> *anomalyVec;

    //constructor
    resultCommand(DefaultIO *dio, HybridAnomalyDetector *ptr, vector<AnomalyReport> *pVector) :
            Command(dio, "upload anomalies and analyze results") {
        this->ptrHybrid = ptr;
        this->anomalyVec = pVector;
    };

    static vector<int> strVecToIntVec(vector<string> &orgVector) {
        vector<int> newVector;
        newVector.reserve(orgVector.size());
        for (string &value: orgVector) {
            newVector.emplace_back(stoi(value));
        }
        return newVector;
    }

    static vector<string> strToVec(string input, const char *separator) {
        vector<string> output;
        char *str = &input[0];
        // Returns first token
        char *token = strtok(str, separator);
        // Keep printing tokens while one of the
        // delimiters present in str[].
        while (token != nullptr) {
            output.emplace_back(token);
            token = strtok(nullptr, separator);
        }
        return output;
    }

    //merge all the report with the same area of time and description
    static vector<pair<pair<int, int>, string>> mergeReport(vector<AnomalyReport> reportVec) {
        vector<pair<pair<int, int>, string>> mergeReport = vector<pair<pair<int, int>, string>>();
        mergeReport.emplace_back(make_pair(reportVec[0].timeStep, reportVec[0].timeStep),
                                 reportVec[0].description);
        int index = 0;
        for (int i = 1; i < reportVec.size(); ++i) {
            if (reportVec[i - 1].description == reportVec[i].description) {
                mergeReport[index].first.second = reportVec[i].timeStep;
            } else {
                mergeReport.emplace_back(make_pair(reportVec[i].timeStep, reportVec[i].timeStep),
                                         reportVec[i].description);
                index++;
            }
        }
        return mergeReport;
    }

    static bool isIntersection(pair<int, int> result, pair<int, int> reporting) {
        //case - there is a full  contain
        if ((result.first >= reporting.first && result.second <= reporting.second) ||
            (result.first <= reporting.first && result.second >= reporting.second)) {
            return true;
        }
        //case 2  - partial Intersection
        if ((result.first <= reporting.first && result.second >= reporting.first) ||
            (result.first <= reporting.second && result.second >= reporting.second)) {
            return true;
        }
        return false;
    }

    static string floatToStringSub(float num) {
        bool changed = false;
        vector<string> vec = strToVec(to_string(num), ".");
        vec[1] = vec[1].substr(0, 3);
        string str = vec[1];
        char *ptrChar = &str[0];
        for (int i = (int) strlen(ptrChar) - 1; i >= 0; --i) {
            if (ptrChar[i] != '0') {
                vec[1] = vec[1].substr(0, i + 1);
                changed = true;
                break;
            }
        }
        if (!changed)
            return vec[0];
        return vec[0] + "." + vec[1];
    }


    vector<pair<int, int>> inputAnomaly() {
        vector<pair<int, int>> vectorResult = vector<pair<int, int>>();
        this->getDefaultIO()->write("Please upload your local anomalies file.\n");
        string inputRead;
        // get the path csv from the usr
        inputRead = "trueAnomaly.csv";
        this->readCSV(inputRead);
        this->getDefaultIO()->write("Upload complete.\n");

        //star read the file
        ifstream inputFile("trueAnomaly.csv"); // the file that I need to upload to the server
        // Open an existing file
        if (!inputFile.is_open()) throw runtime_error("Could not open file");
        string line;
        while (getline(inputFile, line)) {
            auto *inputVector = new vector<string>(strToVec(line, ","));
            vector<int> input = strVecToIntVec(*inputVector);
            pair<int, int> pair = make_pair(input[0], input[1]);
            vectorResult.push_back(pair);
            delete inputVector;
        }
        inputFile.close();
        return vectorResult;
    }

    virtual void execute() override {
        //get the input from the user and return a vector contain a pair <star anomaly, end anomaly>)
        vector<pair<int, int>> vectorResult = inputAnomaly();
        vector<pair<pair<int, int>, string>> mergeReportVec = mergeReport(*this->anomalyVec);
        int TP = 0;
        //check the intersection with the result from the detector
        for (const pair<pair<int, int>, string> &reporting: mergeReportVec) {
            for (pair<int, int> result: vectorResult) {
                if (isIntersection(reporting.first, result)) {
                    TP++;
                }
            }
        }
        int n = this->ptrHybrid->EventNum;
        //roundf(x * 100) / 100.0
        float FP = (float) mergeReportVec.size() - (float) TP;
        float TPR = (float) TP / (float) vectorResult.size();
        float FPN = FP / (float) n;
        string TPRstring = floatToStringSub(TPR);
        string FPNstring = floatToStringSub(FPN);
        this->getDefaultIO()->write("True Positive Rate: " + TPRstring + "\n");
        this->getDefaultIO()->write("False Positive Rate: " + FPNstring + "\n");
    }

};

#endif /* COMMANDS_H_ */
