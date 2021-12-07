
#include "StandardIO.h"
#include <cstring>

string StandardIO::read(){
    string readInput;
    cin >> readInput;
    return readInput;
};

 void StandardIO::write(string text) {
     char* ptr;
     char *ptrText = &text[0];
     ptr = strtok(ptrText,",");

     ifstream  src(text, ios::binary);
     ofstream  dst("InputCsv", ios::binary);
     dst << src.rdbuf();
 }
