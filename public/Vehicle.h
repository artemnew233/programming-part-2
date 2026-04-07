#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
public:
    Vehicle(const std::string& manufacturer, int year);
    virtual ~Vehicle() = default;
    virtual void displayInfo() const;
    std::string getManufacturer() const;
    int getYear() const;

private:
    std::string manufacturer;
    int year;
};

#endif
