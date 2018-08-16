#ifndef __CHECKER_H
#define __CHECKER_H

#include "inc.h"

class Checker {
private:
    AbstractProgram compileResult;
    
public:
    explicit Checker(const Compiler& compiler): compileResult(compiler.compileResult) {}
    void check();

private:
    void checkEmptyItem();
    void checkInputTape();
    void checkTransFunc();
};

#endif // !__CHECKER_H