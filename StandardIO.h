//* Author: 318509700 Peleg
//*         207984956 Nadav

#ifndef STANDARDIO_H_
#define STANDARDIO_H_

#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "commands.h"

using namespace std;

class StandardIO : public DefaultIO {
public:
    virtual string read();

    virtual void write(string text);

    virtual void write(float f);

    virtual void read(float *f);

    virtual ~StandardIO() {}

};

#endif /* STANDARDIO_H_ */