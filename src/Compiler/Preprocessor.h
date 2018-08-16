#ifndef __PREPROCESSOR_H
#define __PREPROCESSOR_H

#include "inc.h"

class Preprocessor {
private:
    ProgFile& progFile;
public:
    explicit Preprocessor(ProgFile& prog):
        progFile(prog) {};

    void run();
};

#endif // !__PREPROCESSOR_H
