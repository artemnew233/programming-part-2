#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"

class Truck : public Vehicle {
public:
    Truck(const std::string& manufacturer, int year, double payloadCapacity);
    void displayInfo() const override;
    double getPayloadCapacity() const;

private:
    double payloadCapacity;
};

#endif
