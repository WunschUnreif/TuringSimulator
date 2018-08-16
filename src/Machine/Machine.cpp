#include "Machine.h"

Machine::Machine(const std::string& mchDscpFile) {

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

void Machine::step() {
    auto currDscp = std::make_pair(currState, *pos);
    auto nextIt = transFunc.find(currDscp);
    if(nextIt == transFunc.end()) {
        mchFlag = MachineFlag::UNDEF;
        return;
    }

    int nextState = std::get<0>(nextIt->second);
    char toWrite = std::get<1>(nextIt->second);
    bool leftMove = std::get<2>(nextIt->second);

    *pos = toWrite;

    if(leftMove && pos != tape.begin()) --pos;
    if(!leftMove) ++pos;
    if(pos == tape.end()) {
        mchFlag = MachineFlag::OVERFLOW;
        return;
    }

    currState = nextState;
    if(currState == acceptState) {
        mchFlag = MachineFlag::ACCEPT;
    } else if(currState == rejectState) {
        mchFlag = MachineFlag::REJECT;
    }
}

void Machine::run() {
    while(mchFlag == MachineFlag::NORMAL) {
        step();
        switch(mchFlag) {
            case MachineFlag::NORMAL: singleStepISR(*this); break;
            case MachineFlag::ACCEPT:  onAccept(*this); break;
            case MachineFlag::REJECT: onReject(*this); break;
            case MachineFlag::OVERFLOW: onOverflow(*this); break;
            case MachineFlag::UNDEF: onUndef(*this); break;
        }
    }
}
