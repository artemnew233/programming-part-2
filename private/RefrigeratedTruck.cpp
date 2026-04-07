#include "../public/RefrigeratedTruck.h"
#include <iostream>

RefrigeratedTruck::RefrigeratedTruck(const std::string& m, int y, double pc, double mt)
    : Truck(m, y, pc), minTemperature(mt) {}

void RefrigeratedTruck::displayInfo() const {
    Truck::displayInfo();
    std::cout << "Special Feature: Refrigerated, Min Temperature: " << minTemperature << " C" << std::endl;
}

double RefrigeratedTruck::getMinTemperature() const { return minTemperature; }
