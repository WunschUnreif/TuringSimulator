#include "inc.h"

void Checker::check() {
    checkEmptyItem();
    checkInputTape();
    checkTransFunc();
}

void Checker::checkEmptyItem() {
    if(compileResult.inputAlphabet.empty()) {
        throw std::runtime_error(
            "missing input alphabet"
        );
    }

    if(compileResult.tapeAlphabet.empty()) {
        throw std::runtime_error(
            "missing tape alphabet"
        );
    }

    if(compileResult.stateNum <= 0) {
        throw std::runtime_error(
            "missing state definitions"
        );
    }

    if(compileResult.maxLength <= 0) {
        throw std::runtime_error(
            "illegal max length"
        );
    }

    if(compileResult.startState.empty()) {
        throw std::runtime_error(
            "missing start state"
        );
    }

    if(compileResult.stateID.count(compileResult.startState) == 0) {
        throw std::runtime_error(
            "start state doesn't exist"
        );
    }
}

void Checker::checkInputTape() {
    for(auto c : compileResult.inputAlphabet) {
        if(compileResult.tapeAlphabet.count(c) == 0) {
            throw std::runtime_error(
                "illegal character in input alphabet"
            );
        }
    }
}

void Checker::checkTransFunc() {
    for(auto pair : compileResult.transFunc) {
        std::string prevState = pair.first.first;
        char chr = pair.first.second;
        std::string nextState = std::get<0>(pair.second);
        char chw = std::get<1>(pair.second);

        if(compileResult.stateID.count(prevState) == 0) {
            throw std::runtime_error(
                "state " + prevState + " does not exist"
            );
        }

        if(compileResult.stateID.count(nextState) == 0) {
            throw std::runtime_error(
                "state " + nextState + " does not exist"
            );
        }

        if(compileResult.tapeAlphabet.count(chr) == 0 && chr != '.') {
            throw std::runtime_error(
                "illegal character at state " + prevState
            );
        }

        if(compileResult.tapeAlphabet.count(chw) == 0 && chw != '.') {
            throw std::runtime_error(
                "illegal character at state " + prevState
            );
        }
    }
}
