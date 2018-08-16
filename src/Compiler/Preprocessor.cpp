#include "inc.h"

void Preprocessor::run() {
    progFile.reset();

    while(!progFile.atTail()) {
        if(progFile.getch() == '#') {
            while(progFile.getch() != '\n') {
                progFile.getch() = ' ';
                progFile.next();
            }
        }
        progFile.next();
    }

    progFile.reset();
}
