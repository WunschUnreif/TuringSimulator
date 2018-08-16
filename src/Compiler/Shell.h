#ifndef __SHELL_H
#define __SHELL_H

#include "inc.h"

class CompilerShell {
public:
    MachineProgram result;
    void compileProgram(const std::string& filename);
};

#endif // !__SHELL_H