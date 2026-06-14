#include "lab18/route.hpp"

#include <iostream>

int main() {
    lab18::Route route({
        {"Depot",      0.0,  0.0},
        {"Customer A", 3.0,  4.0},
        {"Customer B", 6.0,  0.0},
        {"Customer C", 9.0,  4.0},
        {"Return",    12.0,  0.0},
    });

    std::cout << "Points:          " << route.size()           << '\n';
    std::cout << "Total length:    " << route.totalLength()    << '\n';
    std::cout << "Longest segment: " << route.longestSegment() << '\n';
    std::cout << "Longest starts at index: "
              << route.longestSegmentIndex() << '\n';

    route.addPoint({"Extra", 15.0, 0.0});
    std::cout << "After addPoint, total: " << route.totalLength() << '\n';

    lab18::Route empty({});
    std::cout << "Empty route length: " << empty.totalLength() << '\n';

    return 0;
}
