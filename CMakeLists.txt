cmake_minimum_required(VERSION 3.10)
project(Lab05)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(public)

add_executable(lab05
    main.cpp
    private/University.cpp
    private/Department.cpp
    private/Professor.cpp
    private/Student.cpp
    private/Course.cpp
)
