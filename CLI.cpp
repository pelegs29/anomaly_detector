//* Author: 318509700 Peleg
//*         207984956 Nadav

#include "CLI.h"
#include <cctype>

using namespace std;

void CLI::buildCommandVector() {
    Command *upload = new UploadCommand(this->dio);
    this->commandsVector.push_back(upload);
    Command *corle = new correlCommand(this->dio, &this->correlation);
    this->commandsVector.push_back(corle);
    Command *detect = new HybridCommand(this->dio, this->hybridAnomalyDetector, &this->anomalyReportVec);
    this->commandsVector.push_back(detect);
    Command *anomaly = new anomalyCommand(this->dio, this->hybridAnomalyDetector, &this->anomalyReportVec);
    this->commandsVector.push_back(anomaly);
}


void printWelcomeMenu() {
    cout << "Welcome to the Anomaly Detection Server." << endl <<
         "Please choose an option:" << endl;
}

int returnOption(string input) {
    if (1 != input.length() || 0 == isdigit(input[0]))
        return -1;
    int givenInput = stoi(input);
    if (givenInput >= 1 && givenInput <= 6)
        return givenInput;
    return -1;
}

void CLI::start() {
    printWelcomeMenu();
    while (true) {
        int currentIndex = 1;
        for (Command *cmd: commandsVector) {
            cout << currentIndex << ". " << cmd->getDesc() << endl;
            currentIndex++;
        }
        cout << currentIndex << ". exit" <<endl;
        int input;
        input = returnOption(dio->read());
        if (input == -1)
            throw "Option given is not valid";
        if (input == commandsVector.size() + 1)
            break;
        commandsVector[input - 1]->execute();
    }
}


