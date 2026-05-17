cmake_minimum_required(VERSION 3.20)
project(lab05 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(LIB_SOURCES
    private/Citizen.cpp
    private/Hospital.cpp
    private/School.cpp
    private/District.cpp
    private/City.cpp
)


add_library(city_services ${LIB_SOURCES})
target_include_directories(city_services PUBLIC public)
target_compile_features(city_services PUBLIC cxx_std_20)
if(MSVC)
    target_compile_options(city_services PRIVATE /W4)
else()
    target_compile_options(city_services PRIVATE -Wall -Wextra -Wpedantic)
endif()



add_executable(lab05_app main.cpp)
target_link_libraries(lab05_app PRIVATE city_services)


add_executable(lab05_tests tests/test_city_services.cpp)
target_link_libraries(lab05_tests PRIVATE city_services GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab05_tests)
