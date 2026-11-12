#include "computations.h"
#include <iostream>

int main() {
    std::cout << "Lab #5 (Variant 5)\n";
    std::cout << "Computations: A1, A2, B1, B2, C, D, F\n";
    std::cout << "Slow: A1, B2 (7s) | Fast: A2, B1, C, D, F (1s)\n";
    std::cout << "Dependencies: A2(A1), B2(B1), F(C), D(A2, B2)\n";
    std::cout << "Schedule: 9.0s (peak 3 threads, 2 async tasks)\n";

    work();

    return 0;
}
