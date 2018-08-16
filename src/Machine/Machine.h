#ifndef MACHINE_H
#define MACHINE_H

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <utility>
#include <functional>
#include <set>
#include <exception>

class Machine {
public:
    enum MachineFlag {
        NORMAL,
        ACCEPT,
        REJECT,
        UNDEF,
        OVERFLOW
    };

private:
    std::map<std::pair<int, char>, std::tuple<int, char, bool>> transFunc;
    int maxLength;
    int stateNum, acceptState, rejectState, startState;
    std::function<void(const Machine&)> onAccept, onReject, onUndef, onOverflow;
    std::function<void(const Machine&)> singleStepISR;

    std::set<char> inputAlphabet, tapeAlphabet;

public:
    std::vector<char> tape;
    std::vector<char>::iterator pos;
    int currState;
    MachineFlag mchFlag;

public:
    explicit Machine(const std::string& mchDscpFile);

    void bindAccept(std::function<void(const Machine&)> onAcceptCb);
    void bindReject(std::function<void(const Machine&)> onRejectCb);
    void bindUndef(std::function<void(const Machine&)> onUndefCb);
    void bindOverflow(std::function<void(const Machine&)> onOverflowCb);
    void bindSigleStepISR(std::function<void(const Machine&)> ssISR);

    void resetMachine();
    void input(const std::string& inputTape);

    void run();

private:
    void step();
};

#endif
