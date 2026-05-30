cmake_minimum_required(VERSION 3.20)
project(lab13 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_library(lab13_lib
    private/StringUtils.cpp
    private/Record.cpp
    private/ReportBuilder.cpp)
target_include_directories(lab13_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)
target_compile_features(lab13_lib PUBLIC cxx_std_20)
target_compile_options(lab13_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lab13_app main.cpp)
target_link_libraries(lab13_app PRIVATE lab13_lib)
target_compile_features(lab13_app PRIVATE cxx_std_20)

add_executable(lab13_tests tests/test_text_processing.cpp)
target_link_libraries(lab13_tests PRIVATE lab13_lib GTest::gtest_main)
target_compile_features(lab13_tests PRIVATE cxx_std_20)
include(GoogleTest)
gtest_discover_tests(lab13_tests)
