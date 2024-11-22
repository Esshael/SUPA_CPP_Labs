#include <iostream>

namespace A {
    void print() {
        std::cout << "Printing from A!" << std::endl;
    }
}

namespace B {
    void print() {
        std::cout << "Printing from B!" << std::endl;
    }
}

int main() {
    A::print();  // print in A
    B::print();  // print in B
    return 0;
}
