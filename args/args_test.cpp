#include <iostream>

#include "args.h"

int main(int argc, char** argv) {
    args::Args args = args::getArguments(argc, argv);

    std::cout << "Arguments provided:\n";
    std::cout << "is_valid:\t" << args.valid.is_valid << "\n";
    std::cout << "is_default:\t" << args.valid.is_default << "\n";
    std::cout << "reason:\t" << args.valid.reason << "\n";

    std::cout << "max:\t\t" << args.max << "\n";
    std::cout << "level:\t\t" << args.level << "\n";
    std::cout << "table:\t\t" << args.table << "\n";
    std::cout << "\n";
}
