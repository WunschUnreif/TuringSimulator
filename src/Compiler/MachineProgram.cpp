#include "inc.h"

void MachineProgram::print() {
    using std::cout;
    using std::endl;
    using std::get;

    cout << "state num: " << stateNum << endl;
    cout << "max length: " << maxLength << endl;
    cout << "start state: " << startState << endl;
    cout << "ac state: " << acceptState << endl;
    cout << "rj state: " << rejectState << endl;
    for(auto pair : transFunc) {
        cout << "(" << pair.first.first
            << ',' << pair.first.second
            << ") -> (" << get<0>(pair.second)
            << ',' << get<1>(pair.second)
            << ',' << get<2>(pair.second)
            << ")" << endl;
    }
}
