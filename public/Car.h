#ifndef CAR_H
#define CAR_H

#include <string>
#include <vector>
#include "Engine.h"
#include "Wheel.h"
#include "Seat.h"
#include "Transmission.h"

class Car {
public:
    Car(const std::string& model, int hp, const std::string& engineType, int wheelSize, const std::string& tireType, int numSeats, const std::string& seatMaterial, int numGears, const std::string& transType);
    void drive();
    void stop();
    std::string getModel() const;
    const Engine& getEngine() const;
    const std::vector<Wheel>& getWheels() const;
    const std::vector<Seat>& getSeats() const;
    const Transmission& getTransmission() const;

private:
    std::string model;
    Engine engine;             // Composition
    std::vector<Wheel> wheels; // Composition (4 wheels)
    std::vector<Seat> seats;   // Composition
    Transmission transmission; // Composition
};

#endif
