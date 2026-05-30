cmake_minimum_required(VERSION 3.20)
project(lab15 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_library(lab15_lib src/Record.cpp src/Algorithms.cpp)
target_include_directories(lab15_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(lab15_lib PUBLIC cxx_std_20)
target_compile_options(lab15_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lab15_app src/main.cpp)
target_link_libraries(lab15_app PRIVATE lab15_lib)
target_compile_features(lab15_app PRIVATE cxx_std_20)

add_executable(lab15_tests tests/AlgorithmTests.cpp)
target_link_libraries(lab15_tests PRIVATE lab15_lib GTest::gtest_main)
target_compile_features(lab15_tests PRIVATE cxx_std_20)
include(GoogleTest)
gtest_discover_tests(lab15_tests)
