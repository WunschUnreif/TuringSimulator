#include "Machine/Machine.h"

int main() {
    std::string mchDscpFile;
    std::cout << "Program name: ";
    std::cin >> mchDscpFile;

    Machine machine(mchDscpFile);
    machine.resetMachine();

    auto printTape = [](const Machine& mch) {
        for(int i = 0; i < mch.tape.size(); ++i) std::cout << '-';
        std::cout << std::endl;
        std::cout << "Current state: " << mch.currState << std::endl;

        int pos = mch.pos - mch.tape.begin();
        for(int i = 0; i < pos; ++i) std::cout << ' ';
        std::cout << 'v';
        for(int i = pos + 1; i < mch.tape.size(); ++i) std::cout << ' ';
        std::cout << std::endl;

        for(auto c : mch.tape) {
            std::cout << c;
        }
        std::cout << std::endl;

        for(int i = 0; i < mch.tape.size(); ++i) std::cout << '-';
        std::cout << std::endl;
    };

    machine.bindSigleStepISR([&](const Machine& mch) {
        printTape(mch);
        std::cin.get();
    });

    machine.bindAccept([&](const Machine& mch) {
        std::cout << "-----Accept State-----" << std::endl;
        printTape(mch);
    });

    machine.bindReject([&](const Machine& mch) {
        std::cout << "-----Reject State-----" << std::endl;
        printTape(mch);
    });

    machine.bindUndef([&](const Machine& mch) {
        std::cout << "-----Undefined State-----" << std::endl;
        printTape(mch);
    });

    machine.bindOverflow([&](const Machine& mch) {
        std::cout << "-----Tape used up-----" << std::endl;
        printTape(mch);
    });

    std::string inputs;
    std::cout << "Input string:" << std::endl;
    std::getline(std::cin, inputs);
    std::getline(std::cin, inputs);

    try {
        machine.input(inputs);
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(0);
    }

    machine.run();

    std::cout << "Finished" << std::endl;

    return 0;
}