#include "../public/Wheel.h"
#include <iostream>

Wheel::Wheel(int s, const std::string& tt) : size(s), tireType(tt) {}

int Wheel::getSize() const { return size; }
std::string Wheel::getTireType() const { return tireType; }

void Wheel::rotate() {
    std::cout << "Wheel (Size " << size << ", " << tireType << ") rotating." << std::endl;
}
