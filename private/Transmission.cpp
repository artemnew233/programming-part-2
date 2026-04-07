#include "../public/Transmission.h"
#include <iostream>

Transmission::Transmission(int g, const std::string& t) : gears(g), type(t), currentGear(0) {}

int Transmission::getGears() const { return gears; }
std::string Transmission::getType() const { return type; }

void Transmission::shift(int gear) {
    if (gear >= 0 && gear <= gears) {
        currentGear = gear;
        std::cout << "Shifted to gear: " << currentGear << " (" << type << ")" << std::endl;
    } else {
        std::cout << "Invalid gear!" << std::endl;
    }
}

int Transmission::getCurrentGear() const { return currentGear; }
