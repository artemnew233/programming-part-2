cmake_minimum_required(VERSION 3.20)
project(lab16 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(lab16_app src/main.cpp)
target_include_directories(lab16_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(lab16_app PRIVATE cxx_std_20)
target_compile_options(lab16_app PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lab16_tests
    tests/test_forward_list.cpp
    tests/test_algorithms.cpp
    tests/test_const_iteration.cpp
    tests/test_simple_vector.cpp)
target_include_directories(lab16_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(lab16_tests PRIVATE GTest::gtest_main)
target_compile_features(lab16_tests PRIVATE cxx_std_20)
target_compile_options(lab16_tests PRIVATE -Wall -Wextra -Wpedantic)
include(GoogleTest)
gtest_discover_tests(lab16_tests)
