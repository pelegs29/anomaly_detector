//* Author: 318509700 Peleg
//*         207984956 Nadav

#ifndef COMMANDS_H_
#define COMMANDS_H_
#include<iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include "CLI.h"
using namespace std;

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}

    // you may add additional methods here
};

// you may add here helper classes


// you may edit this class
class Command {
    string description;
    DefaultIO *dio;

public:
    Command(string desc, DefaultIO *dio) : dio(dio), description(desc) {}

    virtual void execute() = 0;

    virtual ~Command() {}

    string getDesc() {
        return this->description;
    }
    DefaultIO* getDefaultIO(){
        return this->dio;
    }
};

// implement here your command classes



#endif /* COMMANDS_H_ */
