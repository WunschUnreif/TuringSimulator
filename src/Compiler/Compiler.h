#ifndef __COMPILER_H
#define __COMPILER_H

#include "inc.h"

class Compiler {
public:
    AbstractProgram compileResult;

private:
    ProgFile& progFile;

public:
    explicit Compiler(ProgFile& file): progFile(file) {}
    void startCompile();

private:
    void inputTable();
    void tapeTable();
    void state();
    void start();
    void len();

    bool readRule(std::string& stateName);
    void registerSpecialState(std::string& stateName);

    void charAssert(char ch);
    void stringAssert(std::string& s);
    void structureCharAssert(char ch);

    std::string errorPos();
};

#endif // !__COMPILER_H