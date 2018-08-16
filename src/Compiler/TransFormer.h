#ifndef __TRANSFORMER_H
#define __TRANSFORMER_H

#include "inc.h"

class Transformer {
public:
    MachineProgram transformResult;
    
private:
    AbstractProgram compileResult;

public:
    explicit Transformer(const Compiler& compiler): compileResult(compiler.compileResult) {}
    void startTransform();
};

#endif // !__TRANSFORMER_H