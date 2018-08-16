#include "inc.h"

int main() {
    ProgFile file("test.tm");
    Preprocessor pp(file);
    pp.run();
    while(!file.atTail()) {
        std::cout << file.getch();
        file.next();
    }
    file.reset();
    std::string token;
    while(!(token = file.readToken()).empty()) {
        std::cout << token << std::endl;
    }
    return 0;
}
