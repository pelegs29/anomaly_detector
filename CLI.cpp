//* Author: 318509700 Peleg
//*         207984956 Nadav

#include "CLI.h"
#include <cctype>

using namespace std;

void CLI::buildCommandVector() {
    Command *upload = new UploadCommand(this->dio, this->data);
    this->commandsVector.push_back(upload);
    Command *correlation = new correlationCommand(this->dio, this->data);
    this->commandsVector.push_back(correlation);
    Command *detect = new DetectCommand(this->dio, this->data);
    this->commandsVector.push_back(detect);
    Command *anomaly = new anomalyCommand(this->dio, this->data);
    this->commandsVector.push_back(anomaly);
    Command *resultAnomaly = new resultCommand(this->dio, this->data);
    this->commandsVector.push_back(resultAnomaly);
}

void CLI::start() {
    while (true) {
        this->dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
        int currentIndex = 1;
        for (Command *cmd: commandsVector) {
            this->dio->write(to_string(currentIndex) + "." + cmd->getDesc() + "\n");
            currentIndex++;
        }
        this->dio->write(to_string(currentIndex) + ".exit\n");
        float fInput;
        this->dio->read(&fInput);
        int input = (int) fInput;
        if (input <= 0 || input > currentIndex) {
            this->dio->write("Option given is not valid");
            continue;
        }
        if (input == commandsVector.size() + 1)
            break;
        commandsVector[input - 1]->execute();
    }
}

CLI::~CLI() {
    delete this->data;
    for (Command *command: this->commandsVector) {
        delete command;
    }
}



