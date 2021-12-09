
#include "StandardIO.h"


using namespace std;

string StandardIO::read(){
    string readInput;
    cin >> readInput;
    return readInput;
};

 void StandardIO::write(string text) {
     vector<string> input = inputString(text);
     string src = input[0];
     string desName = input[1];
     // File input pointer
     ofstream outfile(desName);
     ifstream inputFile(src); // the file that i need to upload to the server
     // Open an existing file
     if(!inputFile.is_open()) throw runtime_error("Could not open file");
     string line;
     while (  getline( inputFile, line ))
     {
         if (line == "done"){
             break;
         }
         outfile << line +"\n";
         //outfile.write(&line[0],line.size());
     }
     outfile.close();
     inputFile.close();
 }


void StandardIO::write(float f) {

}

void StandardIO::read(float *f) {

}


vector<string> StandardIO::inputString(string input) {
    vector<std::string> output;
    char *str = &input[0];
// Returns first token
    char *token = strtok(str, ",");
// Keep printing tokens while one of the
// delimiters present in str[].
    while (token != nullptr) {
        output.emplace_back(token);
        token = strtok(nullptr, ",");
    }
    return output;
}
