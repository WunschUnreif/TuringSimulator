#include "inc.h"

void CompilerShell::compileProgram(const std::string& filename) {
    ProgFile file(filename);
    Preprocessor pp(file);
    pp.run();
    
    try {
        Compiler compiler(file);
        compiler.startCompile();

        Checker checker(compiler);
        checker.check();

        Transformer transformer(compiler);
        transformer.startTransform();

        result = transformer.transformResult;
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(0);
    }
}