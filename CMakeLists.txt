cmake_minimum_required(VERSION 3.10)
project(Lab06)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(public)

add_executable(lab06
    main.cpp
    private/Car.cpp
    private/Engine.cpp
    private/Wheel.cpp
    private/Seat.cpp
    private/Transmission.cpp
)
