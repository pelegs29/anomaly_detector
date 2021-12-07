//* Author: 318509700 Peleg
//*         207984956 Nadav

#ifndef SIMPLE_EXAMPLE_UPLOADCOMMAND_H
#define SIMPLE_EXAMPLE_UPLOADCOMMAND_H

#include "commands.h"

class UploadCommand : public Command {
    //const string description = "upload a time series csv file";
public:
    UploadCommand(DefaultIO *dio,CLI* cli) : Command("upload a time series csv file", dio) {
    }
    virtual void execute();

};

#endif //SIMPLE_EXAMPLE_UPLOADCOMMAND_H
