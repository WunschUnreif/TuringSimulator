#include "inc.h"

int main() {
    ProgFile file("test.tm");
    Preprocessor pp(file);
    Compiler c(file);
    pp.run();
    c.startCompile();
    c.compileResult.print();
    return 0;
}
