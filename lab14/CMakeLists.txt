cmake_minimum_required(VERSION 3.20)
project(lab14 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_library(lab14_lib src/Record.cpp src/ContainerExperiments.cpp src/ContainerReport.cpp)
target_include_directories(lab14_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(lab14_lib PUBLIC cxx_std_20)
target_compile_options(lab14_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lab14_app src/main.cpp)
target_link_libraries(lab14_app PRIVATE lab14_lib)
target_compile_features(lab14_app PRIVATE cxx_std_20)

add_executable(lab14_tests tests/SequenceContainerTests.cpp)
target_link_libraries(lab14_tests PRIVATE lab14_lib GTest::gtest_main)
target_compile_features(lab14_tests PRIVATE cxx_std_20)
include(GoogleTest)
gtest_discover_tests(lab14_tests)
