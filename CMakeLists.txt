cmake_minimum_required(VERSION 3.10)
project(Lab07)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(public)

add_executable(lab07
    main.cpp
    private/Vehicle.cpp
    private/Truck.cpp
    private/RefrigeratedTruck.cpp
    private/PassengerCar.cpp
)
