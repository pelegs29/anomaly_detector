//* Author: 318509700 Peleg
//*         207984956 Nadav

#include "CLI.h"
#include <cctype>

using namespace std;

void printMenu() {
    printf("Welcome to the Anomaly Detection Server.\n"
           "Please choose an option:\n"
           "1.upload a time series csv file\n"
           "2.algorithm settings\n"
           "3.detect anomalies\n"
           "4.display results\n"
           "5.upload anomalies and analyze results\n"
           "6.exit\n");
}

int returnOption(string input) {
    if (1 != input.length() || 0 == isdigit(input[0]))
        return -1;
    int givenInput = stoi(input);
    if (givenInput >= 1 && givenInput <= 6)
        return givenInput;
    return -1;
}

CLI::CLI(DefaultIO *dio) {
}

void CLI::start() {
    while (true) {
        printMenu();
        int input;
        input = returnOption(dio->read());
        if (input == -1)
            throw "Option given is not valid";
        if (input == 6)
            break;
        commandsVector[input - 1].execute();
    }

}


CLI::~CLI() {
}

