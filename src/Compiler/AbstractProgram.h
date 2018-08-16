#ifndef __ABSTRACT_PROGRAM_H
#define __ABSTRACT_PROGRAM_H

#include "inc.h"

struct AbstractProgram {
    std::set<char> inputAlphabet;
    std::set<char> tapeAlphabet;
    int stateNum = 0;
    int maxLength = 0;
    std::string startState;
    std::string acceptState;
    std::string rejectState;
    std::map<std::string, int> stateID;
    std::map<std::pair<std::string, char>, std::tuple<std::string, char, bool>> transFunc;

    void print();   //for test
};

#endif // !__ABSTRACT_PROGRAM_H
