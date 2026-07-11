cmake_minimum_required(VERSION 3.20)
project(lab17 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(lab17_app src/main.cpp)
target_include_directories(lab17_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(lab17_app PRIVATE cxx_std_20)
target_compile_options(lab17_app PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lab17_tests tests/test_assoc.cpp)
target_include_directories(lab17_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(lab17_tests PRIVATE GTest::gtest_main)
target_compile_features(lab17_tests PRIVATE cxx_std_20)
target_compile_options(lab17_tests PRIVATE -Wall -Wextra -Wpedantic)
include(GoogleTest)
gtest_discover_tests(lab17_tests)
