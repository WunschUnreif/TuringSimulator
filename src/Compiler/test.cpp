#include "inc.h"

int main() {
    ProgFile file("test.tm");
    Preprocessor pp(file);
    Compiler c(file);
    try {
        pp.run();
        c.startCompile();
        Checker chk(c);
        chk.check();
        c.compileResult.print();
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
