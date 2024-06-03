#include <iostream>
#include <vector>
#include "IContainer.hpp"
#include "SerialContainer.hpp"
#include "LinkedListContainer.hpp"
#include "ReservingSerialContainer.hpp"


void fillContainer(IContainer<int>& c) {
    for (int i = 0; i < 10; ++i) {
        c.push_back(i);
    }
}

void printContainer(const char* prologue, IContainer<int>& c,
                    const char* epilogue) {
    std::cout << prologue;
    for (size_t i = 0; i < c.size(); ++i) {
        std::cout << c[i] << " ";
    }
    std::cout << epilogue;
}

void testContainer(IContainer<int>& c) {
    fillContainer(c);
    printContainer("Container initialized:\t", c,
                   "\nExpected:\t\t0 1 2 3 4 5 6 7 8 9\n\n");

    std::cout << "Container's size:\t" << c.size() << "\nExpected:\t\t10\n\n";

    c.erase(6);
    c.erase(4);
    c.erase(2);
    printContainer("Container after deletion:\t", c,
                   "\nExpected:\t\t\t0 1 3 5 7 8 9\n\n");

    c.insert(0, 10);
    printContainer("Container after add 10 to beginning:\t", c,
                   "\nExpected:\t\t\t\t10 0 1 3 5 7 8 9\n\n");

    c.insert(c.size()/2, 20);
    printContainer("Container after add 20 to middle:\t", c,
                   "\nExpected:\t\t\t\t10 0 1 3 20 5 7 8 9\n\n");

    // c.push_back(30);
    c.insert(9, 30);
    printContainer("Container after add 30 to end:\t", c,
                   "\nExpected:\t\t\t10 0 1 3 20 5 7 8 9 30\n\n");
}

int main() {
    // std::cout << "***********************\n";
    // std::cout << "*** SerialContainer ***\n";
    // SerialContainer<int> c1;
    // std::cout << "***********************\n";
    // testContainer(c1);

    // std::cout << "***************************\n";
    // std::cout << "*** LinkedListContainer ***\n";
    // std::cout << "***************************\n";
    // LinkedListContainer<int> c2;
    // testContainer(c2);

    std::cout << "********************************\n";
    std::cout << "*** ReservingSerialContainer ***\n";
    ReservingSerialContainer<int> c3{1.5};
    std::cout << "********************************\n";
    testContainer(c3);

    return 0;
}
