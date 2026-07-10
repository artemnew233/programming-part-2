#include "route_utils.h"
#include <iostream>
#include <typeinfo>

int main() {
    std::cout << "=== longerSegment ===\n";
    std::cout << "longer(5, 8)      = " << longerSegment(5, 8) << "\n";
    std::cout << "longer(10.5, 3.2) = " << longerSegment(10.5, 3.2) << "\n";
    std::cout << "longer(7L, 7L)    = " << longerSegment(7L, 7L) << "\n";

    // --- countSegmentsInRange ---
    std::cout << "\n=== countSegmentsInRange ===\n";
    int segments_i[] = {2, 5, 8, 11, 14};
    std::cout << "int  [2,5,8,11,14] in [5,11]: "
              << countSegmentsInRange(segments_i, 5, 5, 11) << "\n"; // 3

    double segments_d[] = {1.0, 3.5, 5.0, 7.8, 10.0};
    std::cout << "double [1,3.5,5,7.8,10] in [3.5,7.8]: "
              << countSegmentsInRange(segments_d, 5, 3.5, 7.8) << "\n"; // 3

    // boundary values
    std::cout << "boundary [5] in [5,5]: "
              << countSegmentsInRange(segments_i, 5, 5, 5) << "\n"; // 1 

    // no match
    std::cout << "no match [2,5,8,11,14] in [20,30]: "
              << countSegmentsInRange(segments_i, 5, 20, 30) << "\n"; // 0

    // --- averageSpeed ---
    std::cout << "\n=== averageSpeed ===\n";
    std::cout << "speed(100, 2)         = " << averageSpeed(100, 2) << "\n";
    std::cout << "speed(250.0, 4)       = " << averageSpeed(250.0, 4) << "\n";
    std::cout << "speed(150.0f, 3.0)    = " << averageSpeed(150.0f, 3.0) << "\n";

    // zero-time handling
    try {
        averageSpeed(100, 0);
    } catch (const std::invalid_argument& e) {
        std::cout << "zero-time exception: " << e.what() << "\n";
    }

    return 0;
}
