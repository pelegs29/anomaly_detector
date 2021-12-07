//* Author: 318509700 Peleg
//*         207984956 Nadav
#include "UploadCommand.h"



 void UploadCommand::execute(){
    cout<<"Please upload your local train CSV file.";
    string inputRead;
    // get the input from the user
    inputRead = this->getDefaultIO()->read()+",anomalyTest.csv";
    this->getDefaultIO()->write(inputRead);
    cout<<"Upload complete.";



    // for the test file
     cout<<"Please upload your local test CSV file.";
     // get the input from the user
     inputRead = this->getDefaultIO()->read()+",anomalyTrain.csv";
     this->getDefaultIO()->write(inputRead);
     cout<<"Upload complete.";
}
