#include "../public/Vehicle.h"
#include <iostream>

Vehicle::Vehicle(const std::string& m, int y) : manufacturer(m), year(y) {}

void Vehicle::displayInfo() const {
    std::cout << "Vehicle: " << manufacturer << " (" << year << ")" << std::endl;
}

std::string Vehicle::getManufacturer() const { return manufacturer; }
int Vehicle::getYear() const { return year; }
