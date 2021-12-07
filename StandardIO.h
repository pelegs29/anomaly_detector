#include "CLI.h"
class StandardIO : public DefaultIO {
public:
    virtual string read();

    virtual void write(string text);

    virtual void write(float f) ;

    virtual void read(float *f);

    virtual ~StandardIO() {}

};
