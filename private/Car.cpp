#include "../public/Car.h"
#include <iostream>

Car::Car(const std::string& mod, int hp, const std::string& engineType, int wheelSize, const std::string& tireType, int numSeats, const std::string& seatMaterial, int numGears, const std::string& transType)
    : model(mod), engine(hp, engineType), transmission(numGears, transType) {
    
    for (int i = 0; i < 4; ++i) {
        wheels.emplace_back(wheelSize, tireType);
    }
    for (int i = 0; i < numSeats; ++i) {
        seats.emplace_back(seatMaterial, i < 2); // Front seats are heated
    }
}

void Car::drive() {
    std::cout << "Starting to drive " << model << "..." << std::endl;
    engine.start();
    transmission.shift(1);
    for (auto& wheel : wheels) {
        wheel.rotate();
    }
}

void Car::stop() {
    std::cout << "Stopping " << model << "..." << std::endl;
    transmission.shift(0);
    engine.stop();
}

std::string Car::getModel() const { return model; }
const Engine& Car::getEngine() const { return engine; }
const std::vector<Wheel>& Car::getWheels() const { return wheels; }
const std::vector<Seat>& Car::getSeats() const { return seats; }
const Transmission& Car::getTransmission() const { return transmission; }
