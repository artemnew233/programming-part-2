#include <iostream>
#include "public/Car.h"

int main() {
    std::cout << "Laboratory Work 6: Composition" << std::endl;
    std::cout << "Variant 1: Car Assembly" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    // Create a car (Composition - Car owns its parts)
    Car myCar("Tesla Model S", 670, "Electric", 21, "Performance", 5, "Leather", 1, "Direct Drive");

    std::cout << "Car Model: " << myCar.getModel() << std::endl;
    std::cout << "Engine: " << myCar.getEngine().getHorsepower() << " HP " << myCar.getEngine().getType() << std::endl;
    std::cout << "Transmission: " << myCar.getTransmission().getGears() << "-speed " << myCar.getTransmission().getType() << std::endl;
    std::cout << "Number of Wheels: " << myCar.getWheels().size() << " (Size: " << myCar.getWheels()[0].getSize() << ")" << std::endl;
    std::cout << "Number of Seats: " << myCar.getSeats().size() << " (Material: " << myCar.getSeats()[0].getMaterial() << ")" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    myCar.drive();
    std::cout << "---------------------------------" << std::endl;
    myCar.stop();

    return 0;
}
