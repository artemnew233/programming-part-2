#include <iostream>
#include <vector>
#include <memory>
#include "public/Vehicle.h"
#include "public/Truck.h"
#include "public/RefrigeratedTruck.h"
#include "public/PassengerCar.h"

int main() {
    std::cout << "Laboratory Work 7: Inheritance" << std::endl;
    std::cout << "Variant 1: Vehicle Hierarchy" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    std::vector<std::unique_ptr<Vehicle>> fleet;

    fleet.push_back(std::make_unique<Vehicle>("Generic", 2020));
    fleet.push_back(std::make_unique<Truck>("Volvo", 2022, 15000));
    fleet.push_back(std::make_unique<RefrigeratedTruck>("Scania", 2023, 12000, -20.5));
    fleet.push_back(std::make_unique<PassengerCar>("Toyota", 2021, 5));

    for (const auto& v : fleet) {
        v->displayInfo();
        std::cout << "Object Size: " << sizeof(*v) << " bytes" << std::endl;
        std::cout << "---------------------------------" << std::endl;
    }

    // Explaining sizes
    std::cout << "\nSize Analysis (using sizeof):" << std::endl;
    std::cout << "Size of Vehicle: " << sizeof(Vehicle) << " bytes" << std::endl;
    std::cout << "Size of Truck: " << sizeof(Truck) << " bytes" << std::endl;
    std::cout << "Size of RefrigeratedTruck: " << sizeof(RefrigeratedTruck) << " bytes" << std::endl;
    std::cout << "Size of PassengerCar: " << sizeof(PassengerCar) << " bytes" << std::endl;
    std::cout << "Note: The size increases as more state (data members) is added in the derived classes." << std::endl;

    return 0;
}
