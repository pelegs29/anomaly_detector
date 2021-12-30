//* Author: 318509700 Peleg
//*         207984956 Nadav

#include "StandardIO.h"


using namespace std;

string StandardIO::read() {
    string readInput;
    cin >> readInput;
    return readInput;
}

void StandardIO::write(string text) {
    cout << text;
}

void StandardIO::write(float f) {
    cout << f;
}

void StandardIO::read(float *f) {
    string readInput;
    cin >> readInput;
    *f = stof(readInput);
}

