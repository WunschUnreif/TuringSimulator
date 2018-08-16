#include "Machine.h"

Machine::Machine(const std::string& mchDscpFile) :
    maxLength(80),
    stateNum(0),
    acceptState(-1),
    rejectState(-1),
    startState(-1),
    tape(maxLength, 0),
    pos(tape.begin()),
    currState(startState),
    mchFlag(MachineFlag::NORMAL) {

    //compile mchDscpFile.

}

void Machine::bindAccept(std::function<void(const Machine&)> onAcceptCb) {
    onAccept = onAcceptCb;
}

void Machine::bindReject(std::function<void(const Machine&)> onRejectCb) {
    onReject = onRejectCb;
}

void Machine::bindUndef(std::function<void(const Machine&)> onUndefCb) {
    onUndef = onUndefCb;
}

void Machine::bindOverflow(std::function<void(const Machine&)> onOverflowCb) {
    onOverflow = onOverflowCb;
}

void Machine::bindSigleStepISR(std::function<void(const Machine&)> ssISR) {
    singleStepISR = ssISR;
}

void Machine::resetMachine() {
    tape.assign(maxLength, 0);
    pos = tape.begin();
    currState = startState;
    mchFlag = MachineFlag::NORMAL;
}

void Machine::input(const std::string& inputTape) {
    if(inputTape.length() > maxLength) {
        throw std::runtime_error("Input too long");
    }
    for(std::string::size_type i = 0; i < inputTape.length(); ++i) {
        if(inputAlphabet.find(inputTape[i]) == inputAlphabet.end()) {
            throw std::runtime_error("Illegal character in input");
        }
        tape[i] = inputTape[i];
    }
}


