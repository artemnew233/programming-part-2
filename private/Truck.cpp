#include "../public/Truck.h"
#include <iostream>

Truck::Truck(const std::string& m, int y, double pc) : Vehicle(m, y), payloadCapacity(pc) {}

void Truck::displayInfo() const {
    Vehicle::displayInfo();
    std::cout << "Type: Truck, Payload Capacity: " << payloadCapacity << " kg" << std::endl;
}

double Truck::getPayloadCapacity() const { return payloadCapacity; }
