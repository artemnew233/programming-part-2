cmake_minimum_required(VERSION 3.15)
project(lab03_MovieTicket CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab03
    src/MovieTicket.cpp
    src/main.cpp
)

target_include_directories(lab03 PRIVATE include)
