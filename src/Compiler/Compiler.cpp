#include "inc.h"

void Compiler::startCompile() {
    std::string token;
    while(!(token = progFile.readToken()).empty()) {
        if(token == "input") {
            inputTable();
        } else if(token == "tape") {
            tapeTable();
        } else if(token == "len") {
            len();
        } else if(token == "state") {
            state();
        } else if(token == "start") {
            start();
        } else {
            throw std::runtime_error("illegal token found at " + errorPos());
        }
    }
}

void Compiler::inputTable() {
    if(!compileResult.inputAlphabet.empty()) {
        throw std::runtime_error(
            "input alphabet redefined at " + errorPos()
        );
    }

    std::string table = progFile.readToken();
    if(table.empty()) {
        throw std::runtime_error("empty alphabet found at " + errorPos());
    }

    for(auto c : table) {
        if(c == '}') {
            throw std::runtime_error("'}' cannot appera in alphabet!");
        }
        compileResult.inputAlphabet.insert(c);
    }
}

void Compiler::tapeTable() {
    if(!compileResult.tapeAlphabet.empty()) {
        throw std::runtime_error(
            "tape alphabet redefined at " + errorPos()
        );
    }

    std::string table = progFile.readToken();
    if(table.empty()) {
        throw std::runtime_error("empty alphabet found at " + errorPos());
    }

    for(auto c : table) {
        if(c == '}') {
            throw std::runtime_error("'}' cannot appera in alphabet");
        }
        compileResult.tapeAlphabet.insert(c);
    }
}

void Compiler::state() {
    std::string stateName = progFile.readToken();

    if(stateName.empty()) {
        throw std::runtime_error(
            "expect state name at " + errorPos()
        );
    }

    if(compileResult.stateID.count(stateName) != 0){
        throw std::runtime_error(
            "state redefined at " + errorPos()
        );
    }

    compileResult.stateID[stateName] = compileResult.stateNum++;

    char ch = progFile.readChar();
    if(ch == '{') {
        while(readRule(stateName));
    } else if(ch == '=') {
        registerSpecialState(stateName);
    }
}

void Compiler::start() {
    if(!compileResult.startState.empty()) {
        throw std::runtime_error(
            "start state redefined at " + errorPos()
        );
    }

    std::string stateName = progFile.readToken();
    if(stateName.empty()) {
        throw std::runtime_error(
            "expect state name at " + errorPos()
        );
    }

    compileResult.startState = stateName;
}

void Compiler::len() {
    if(compileResult.maxLength != 0) {
        throw std::runtime_error(
            "max length redefined at " + errorPos()
        );
    }

    std::string lenString = progFile.readToken();
    if(lenString.empty()) {
        throw std::runtime_error(
            "expect number at " + errorPos()
        );
    }

    int maxLength = std::stoi(lenString);
    if(maxLength <= 0) {
        throw std::runtime_error("max length must be non-negative");
    }

    compileResult.maxLength = maxLength;
}

bool Compiler::readRule(std::string& stateName) {
    char chr, chw, lr;
    bool left;
    std::string nextState;

    chr = progFile.readChar();
    charAssert(chr);
    if(chr == '}') return false;

    structureCharAssert(':');

    chw = progFile.readChar();
    charAssert(chw);

    structureCharAssert(',');

    lr = progFile.readChar();
    charAssert(lr);
    if(lr == 'L') left = true;
    else if(lr == 'R') left = false;
    else {
        throw std::runtime_error(
            "expect [L/R] at " + errorPos()
        );
    }

    structureCharAssert(',');

    nextState = progFile.readToken();
    stringAssert(nextState);

    std::pair<std::string, char> key = std::make_pair(stateName, chr);
    std::tuple<std::string, char, bool> value = std::make_tuple(nextState, chw, left);

    if(compileResult.transFunc.count(key) != 0) {
        throw std::runtime_error(
            "rule redefined at " + errorPos()
        );
    }

    compileResult.transFunc[key] = value;
}

void Compiler::registerSpecialState(std::string& stateName) {
    std::string token = progFile.readToken();
    stringAssert(token);

    if(token == "accept") {
        if(!compileResult.acceptState.empty()) {
            throw std::runtime_error(
                "accept state redefined at " + errorPos()
            );
        }
        compileResult.acceptState = stateName;
    } else if(token == "reject") {
        if(!compileResult.rejectState.empty()) {
            throw std::runtime_error(
                "reject state redefined at " + errorPos()
            );
        }
        compileResult.rejectState = stateName;
    } else {
        throw std::runtime_error(
            "expect [accept/reject] at " + errorPos()
        );
    }
}

void Compiler::charAssert(char ch) {
    if(ch == 0) {
        throw std::runtime_error(
            "cannot read character at " + errorPos()
        );
    }
}

void Compiler::stringAssert(std::string& s) {
    if(s.empty()) {
        throw std::runtime_error(
            "cannot read string at " + errorPos()
        );
    }
}

void Compiler::structureCharAssert(char ch) {
    if(!progFile.readStructureChar(ch)) {
        throw std::runtime_error(
            "expect structure character at " + errorPos()
        );
    }
}

std::string Compiler::errorPos() {
    std::string col = std::to_string(progFile.colNum());
    std::string row = std::to_string(progFile.lineNum());
    return  "row: " + row + ", col:" + col + ".";
}
