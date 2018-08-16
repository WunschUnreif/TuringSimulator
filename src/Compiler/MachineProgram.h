#ifndef __MACHINE_PROGRAM_H
#define __MACHINE_PROGRAM_H

#include "inc.h"

struct MachineProgram {
    std::set<char> inputAlphabet;
    std::set<char> tapeAlphabet;
    int stateNum = 0;
    int maxLength = 0;
    int startState = -1;
    int acceptState = -1;
    int rejectState = -1;
    std::map<std::pair<int, char>, std::tuple<int, char, bool>> transFunc;

    void print();   //for test
};

#endif // !__MACHINE_PROGRAM_H