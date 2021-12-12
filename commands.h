//* Author: 318509700 Peleg
//*         207984956 Nadav

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <iostream>
#include <cstring>
#include <fstream>
#include <utility>
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

    // add upload and download methods.
};

class CLI_Data {
    HybridAnomalyDetector *hybridAnomalyDetector;
    vector<AnomalyReport> anomalyReportVec;
    float *correlation;
public:
    CLI_Data() {
        this->hybridAnomalyDetector = new HybridAnomalyDetector();
        this->anomalyReportVec = vector<AnomalyReport>();
        this->correlation = &hybridAnomalyDetector->thresholdDetector;
    }

    virtual ~CLI_Data() {
        delete this->hybridAnomalyDetector;
    }

    HybridAnomalyDetector *getHybridAnomalyDetector() {
        return this->hybridAnomalyDetector;
    }


    vector<AnomalyReport> &getAnomalyReportVec() {
        return anomalyReportVec;
    }

    void setAnomalyReportVec(vector<AnomalyReport> ReportVec) {
        this->anomalyReportVec = std::move(ReportVec);
    }

    float *getCorrelation() {
        return correlation;
    }

    void setCorrelation(float correlationInput) {
        *this->correlation = correlationInput;
    }

};


class Command {
    string description;
    DefaultIO *dio;
protected:
    CLI_Data *data;
public:
    // constructor
    Command(DefaultIO *dioIn, const string &descIn, CLI_Data *dataIn) {
        data = dataIn;
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

    /**
     * this method reads from the DefaultIO given the CSV file,
     * each iteration reading a line using the IO.read() func,
     * until the last line given (last line is "done").
     * @param fileName the given file name to write.
     */
    void readCSV(const string &fileName) {
        // File input pointer
        ofstream outfile(fileName);
        string line;
        while (true) {
            line = this->getDefaultIO()->read();
            if (line == "done") {
                break;
            }
            // concat \n at the end of each line.
            outfile << line + "\n";
        }
        outfile.close();
    }
};

class UploadCommand : public Command {
public:

    //constructor
    explicit UploadCommand(DefaultIO *dio, CLI_Data *data) :
            Command(dio, "upload a time series csv file", data) {
    };

    /**
     * this execute func creates 2 csv file : train and test,
     * using the data received from the DefaultIO.
     */
    virtual void execute() override {
        this->getDefaultIO()->write("Please upload your local train CSV file.\n");
        string fileName;
        // get the train csv from the user
        fileName = "anomalyTrain.csv";
        this->readCSV(fileName);
        this->getDefaultIO()->write("Upload complete.\n");

        // for the test file
        this->getDefaultIO()->write("Please upload your local test CSV file.\n");
        // get the input from the user
        fileName = "anomalyTest.csv";
        this->readCSV(fileName);
        this->getDefaultIO()->write("Upload complete.\n");
    }
};

class correlationCommand : public Command {
public:
    correlationCommand(DefaultIO *dio, CLI_Data *data) :
            Command(dio, "algorithm settings", data) {};

    /**
     * this exec func will execute the functionality of correlation threshold change.
     */
    virtual void execute() override {
        this->getDefaultIO()->write("The current correlation threshold is " +
                                    to_string(*this->data->getCorrelation()) + "\n");
        this->getDefaultIO()->write("Type a new threshold\n");
        string newCorrelation = this->getDefaultIO()->read();
        float numInput = stof(&newCorrelation[0]);
        //if the input is not 0-1 the user need to enter again
        while (1 < numInput || 0 > numInput) {
            this->getDefaultIO()->write("please choose a value between 0 and 1.\n");
            newCorrelation = this->getDefaultIO()->read();
            numInput = (float) stoi(&newCorrelation[0]);
        }
        this->data->setCorrelation(numInput);
    }
};


class HybridCommand : public Command {
public:

    //constructor
    HybridCommand(DefaultIO *dio, CLI_Data *data) :
            Command(dio, "detect anomalies", data) {};

    /**
     * this execution method will train and test the csv.
     */
    virtual void execute() override {
        TimeSeries tsTrain = TimeSeries("anomalyTrain.csv");
        data->getHybridAnomalyDetector()->learnNormal(tsTrain);
        TimeSeries tsTest = TimeSeries("anomalyTest.csv");
        data->setAnomalyReportVec(data->getHybridAnomalyDetector()->detect(tsTest));
        this->getDefaultIO()->write("anomaly detection complete.\n");
    }

};


class anomalyCommand : public Command {
public:

    //constructor
    anomalyCommand(DefaultIO *dio, CLI_Data *data) :
            Command(dio, "display results", data) {};

    /**
     * this execute command will print the anomaly report through the default IO.
     */
    virtual void execute() override {
        for (const AnomalyReport &report: data->getAnomalyReportVec()) {
            int row = report.timeStep;
            this->getDefaultIO()->write(to_string(row) + "\t" + report.description + "\n");
        }
        this->getDefaultIO()->write("Done.\n");
    }

};

class resultCommand : public Command {
public:
    //constructor
    resultCommand(DefaultIO *dio, CLI_Data *data) :
            Command(dio, "upload anomalies and analyze results", data) {};

    /**
     * this method will convert a string vector to integer vector
     * @param orgVector inputted vector of string
     * @return the same vector with integer values
     */
    static vector<int> strVecToIntVec(vector<string> &orgVector) {
        vector<int> newVector;
        // allocate space in memory for emplace back func.
        newVector.reserve(orgVector.size());
        for (string &value: orgVector) {
            newVector.emplace_back(stoi(value));
        }
        return newVector;
    }

    /**
     * this method will convert a given string seperated by the separator given into a vector of strings
     * @param input string given.
     * @param separator the indication for separation.
     * @return vector of seperated strings.
     */
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

    /**
     * this method will merge all the reports with the same area of time and description
     * @param reportVec the given reports vector
     * @return vector of pairs of 2 integers and string representing the merged vector.
     */
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

    /**
     * this method will check if an intersection is present in two pairs of int,
     * each pair representing range from int1 to int2
     * @param result result pair
     * @param reporting reporting pair
     * @return true is an intersection is present or false otherwise.
     */
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

    /**
     * this method will convert float to its string representation with precision of 3 numbers after the dot.
     * @param num the given float number.
     * @return a string representing the float number with precision of 3.
     */
    static string floatToStringSub(float num) {
        bool changed = false;
        vector<string> vec = strToVec(to_string(num), ".");
        vec[1] = vec[1].substr(0, 3);
        string str = vec[1];
        char *ptrChar = &str[0];
        // loop that go over each char in the string
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

    /**
     * this method will receive from the user using the DefaultIO the anomalies and creates
     * output vector containing pairs.
     * @return vector of pairs, each pair contain the start and end point of an anomaly.
     */
    vector<pair<int, int>> inputAnomaly() {
        vector<pair<int, int>> vectorResult = vector<pair<int, int>>();
        this->getDefaultIO()->write("Please upload your local anomalies file.\n");
        string fileName;
        // get the path csv from the user
        fileName = "trueAnomaly.csv";
        this->readCSV(fileName);
        this->getDefaultIO()->write("Upload complete.\n");

        //start to read the file
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

    /**
     * this method get the anomalies from the user, merge the conducted report and checks for any intersections
     * between the two.
     * at the end of the execution the method will write the true and negative rate.
     */
    virtual void execute() override {
        //get the input from the user and return a vector contain a pair <star anomaly, end anomaly>)
        vector<pair<int, int>> vectorResult = inputAnomaly();
        vector<pair<pair<int, int>, string>> mergeReportVec = mergeReport(data->getAnomalyReportVec());
        int TP = 0;
        //check the intersection with the result from the detector
        for (const pair<pair<int, int>, string> &reporting: mergeReportVec) {
            for (pair<int, int> result: vectorResult) {
                if (isIntersection(reporting.first, result)) {
                    TP++;
                }
            }
        }
        int n = data->getHybridAnomalyDetector()->EventNum;
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
