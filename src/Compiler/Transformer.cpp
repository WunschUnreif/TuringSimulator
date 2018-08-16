#include "inc.h"

void Transformer::startTransform() {
    compileResult.stateID[""] = -1;

    transformResult.inputAlphabet = compileResult.inputAlphabet;
    transformResult.tapeAlphabet = compileResult.tapeAlphabet;
    transformResult.stateNum = compileResult.stateNum;
    transformResult.maxLength = compileResult.maxLength;
    transformResult.startState = compileResult.stateID[compileResult.startState];
    transformResult.acceptState = compileResult.stateID[compileResult.acceptState];
    transformResult.rejectState = compileResult.stateID[compileResult.rejectState];

    for(auto pair : compileResult.transFunc) {
        std::string prevState = pair.first.first;
        char chr = pair.first.second;
        std::string nextState = std::get<0>(pair.second);
        char chw = std::get<1>(pair.second);
        bool left = std::get<2>(pair.second);

        std::pair<int, char> key = std::make_pair(compileResult.stateID[prevState], chr);
        std::tuple<int, char, bool> value = std::make_tuple(compileResult.stateID[nextState], chw, left);

        transformResult.transFunc[key] = value;
    }
}
