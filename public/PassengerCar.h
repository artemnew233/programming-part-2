#ifndef PASSENGERCAR_H
#define PASSENGERCAR_H

#include "Vehicle.h"

class PassengerCar : public Vehicle {
public:
    PassengerCar(const std::string& manufacturer, int year, int passengerCapacity);
    void displayInfo() const override;
    int getPassengerCapacity() const;

private:
    int passengerCapacity;
};

#endif
