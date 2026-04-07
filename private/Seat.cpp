#include "../public/Seat.h"
#include <iostream>

Seat::Seat(const std::string& mat, bool heat) : material(mat), heated(heat), position(0) {}

std::string Seat::getMaterial() const { return material; }
bool Seat::isHeated() const { return heated; }

void Seat::adjust(int pos) {
    position = pos;
    std::cout << "Seat adjusted to position: " << position << std::endl;
}
