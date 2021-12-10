
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

void StandardIO::write(float f) {}

void StandardIO::read(float *f) {}

