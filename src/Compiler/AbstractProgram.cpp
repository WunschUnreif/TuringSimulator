#include "inc.h"

void AbstractProgram::print() {
    using std::cout;
    using std::endl;
    cout << "state number: " << stateNum << endl;
    for(auto pair : transFunc) {
        cout << '(' << pair.first.first
            << ',' << pair.first.second
            << ") -> ("
            << std::get<0>(pair.second)
            << ',' << std::get<1>(pair.second)
            << ',' << (std::get<2>(pair.second) ? 'L' : 'R')
            << ')'
            << endl;
    }
}
