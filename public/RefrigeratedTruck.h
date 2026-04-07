#ifndef REFRIGERATEDTRUCK_H
#define REFRIGERATEDTRUCK_H

#include "Truck.h"

class RefrigeratedTruck : public Truck {
public:
    RefrigeratedTruck(const std::string& manufacturer, int year, double payloadCapacity, double minTemperature);
    void displayInfo() const override;
    double getMinTemperature() const;

private:
    double minTemperature;
};

#endif
