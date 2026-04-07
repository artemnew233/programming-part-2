#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <string>

class Transmission {
public:
    Transmission(int gears, const std::string& type);
    int getGears() const;
    std::string getType() const;
    void shift(int gear);
    int getCurrentGear() const;

private:
    int gears;
    std::string type;
    int currentGear;
};

#endif
