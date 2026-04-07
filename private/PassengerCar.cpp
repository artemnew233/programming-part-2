#include "../public/PassengerCar.h"
#include <iostream>

PassengerCar::PassengerCar(const std::string& m, int y, int pc) : Vehicle(m, y), passengerCapacity(pc) {}

void PassengerCar::displayInfo() const {
    Vehicle::displayInfo();
    std::cout << "Type: Passenger Car, Passenger Capacity: " << passengerCapacity << std::endl;
}

int PassengerCar::getPassengerCapacity() const { return passengerCapacity; }
