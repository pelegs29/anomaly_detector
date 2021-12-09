//* Author: 318509700 Peleg
//*         207984956 Nadav
#include "UploadCommand.h"


vector<string> inputString(string input) {
    vector<string> output;
    char *str = &input[0];
// Returns first token
    char *token = strtok(str, ">");
// Keep printing tokens while one of the
// delimiters present in str[].
    while (token != nullptr) {
        output.push_back(token);
        token = strtok(nullptr, ">");
    }
    return output;
}


void UploadCommand::execute() {
    this->getDefaultIO()->write("Please upload your local train CSV file.\n");
    string inputRead;
    // get the train csv from the user
    inputRead = "anomalyTrain.csv";
    this->readCSV(inputRead);
    cout << "Upload complete." << endl;

    // for the test file
    this->getDefaultIO()->write("Please upload your local test CSV file.\n");
    // get the input from the user
    inputRead = "anomalyTest.csv";
    this->readCSV(inputRead);
    cout << "Upload complete." << endl;
}

void correlCommand::execute() {
    this->getDefaultIO()->write("The current correlation threshold is " + to_string(*this->correlation) + "\n");
    this->getDefaultIO()->write("Type a new threshold\n");
    string intput = this->getDefaultIO()->read();
    float numInput = stof(&intput[0]);
    //if the input is not 0-1 the user need to enter again
    while (1 < numInput || 0 > numInput) {
        this->getDefaultIO()->write("please choose a value between 0 and 1.\n");
        intput = this->getDefaultIO()->read();
        numInput = atoi(&intput[0]);
    }
    *this->correlation = numInput;
    //cout<<"The current correlation threshold is " << + *this->correlation <<endl;

}


//merge all the report with the same area of time and description
vector<pair<pair<int, int>, string>> mergeReport(vector<AnomalyReport> reportVec) {
    vector<pair<pair<int, int>, string>> mergeReport = vector<pair<pair<int, int>, string>>();
    mergeReport.push_back(make_pair(make_pair(reportVec[0].timeStep, reportVec[0].timeStep), reportVec[0].description));
    int index = 0;
    for (int i = 1; i < reportVec.size(); ++i) {
        if (reportVec[i - 1].description == reportVec[i].description) {
            mergeReport[index].first.second = reportVec[i].timeStep;
        } else {
            mergeReport.push_back(
                    make_pair(make_pair(reportVec[i].timeStep, reportVec[i].timeStep), reportVec[i].description));
            index++;
        }
    }
    return mergeReport;
}


void HybridCommand::execute() {
    TimeSeries tsTrain = TimeSeries("anomalyTrain.csv");
    this->ptrHybrid->learnNormal(tsTrain);
    TimeSeries tsTest = TimeSeries("anomalyTest.csv");
    *this->anomalyVec = this->ptrHybrid->detect(tsTest);
    this->getDefaultIO()->write("anomaly detection complete.\n");
}

void anomalyCommand::execute() {
    for (const AnomalyReport &report: *this->anomalyVec) {
        int row = report.timeStep;
        this->getDefaultIO()->write(to_string(row) + "\t" + report.description + "\n");
    }
    this->getDefaultIO()->write("Done.\n");

}

vector<int> inputStringToInt(string input) {
    vector<int> output;
    char *str = &input[0];
// Returns first token
    char *token = strtok(str, ",");
// Keep printing tokens while one of the
// delimiters present in str[].
    while (token != nullptr) {
        output.push_back(atoi(token));
        token = strtok(nullptr, ",");
    }
    return output;
}

vector<pair<int, int>> resultCommand::inputAnomaly() {
    vector<pair<int, int>> vectorResult = vector<pair<int, int>>();
    this->getDefaultIO()->write("Please upload your local anomalies file.\n");
    string inputRead;
    // get the path csv from the user
    inputRead = "trueAnomaly.csv";
    this->readCSV(inputRead);
    this->getDefaultIO()->write("Upload complete.\n");

    //star read the file
    ifstream inputFile("trueAnomaly.csv"); // the file that i need to upload to the server
    // Open an existing file
    if (!inputFile.is_open()) throw runtime_error("Could not open file");
    string line;
    while (getline(inputFile, line)) {
        vector<int> input = inputStringToInt(line);
        pair<int, int> pair = make_pair(input[0], input[1]);
        vectorResult.push_back(pair);
    }
    inputFile.close();
    return vectorResult;
}

bool isIntersection(pair<int, int> result, pair<int, int> reporting) {
    if ((result.first >= reporting.first && result.second <= reporting.second) ||
        (result.first <= reporting.first && result.second >= reporting.second)) {
        return true;
    }
    if ((result.first <= reporting.first && result.second >= reporting.first) ||
        (result.first >= reporting.first && result.first <= reporting.second)) {
        return true;
    }
    return false;
}

string fixPrecision(float number){
    stringstream ss;
    ss << precision(3) <<
}

void resultCommand::execute() {

    //get the input from the user and return a vector contain a pair <star anomaly, end anomaly>)
    vector<pair<int, int>> vectorResult = inputAnomaly();
    vector<pair<pair<int, int>, string>> mergeReportVec = mergeReport(*this->anomalyVec);
    int TP = 0;
    //check the intersection with the result from the detector
    for (pair<pair<int, int>, string> reporting: mergeReportVec) {
        for (pair<int, int> result: vectorResult) {
            if (isIntersection(reporting.first, result)) {
                TP++;
            }
        }
    }
    int n = this->ptrHybrid->EventNum;
    float FP = mergeReportVec.size() - TP;

    cout.precision(3);
    cout << "True Positive Rate: " << (float) TP / vectorResult.size() << endl;
    cout << "False Positive Rate: " << FP / n << endl;

}
