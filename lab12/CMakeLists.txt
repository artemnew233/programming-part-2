cmake_minimum_required(VERSION 3.20)
project(lab12 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_library(lab12_lib
    private/MessageBuffer.cpp
    private/DomainTypes.cpp)
target_include_directories(lab12_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)
target_compile_features(lab12_lib PUBLIC cxx_std_20)
target_compile_options(lab12_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lab12_app main.cpp)
target_link_libraries(lab12_app PRIVATE lab12_lib)
target_compile_features(lab12_app PRIVATE cxx_std_20)

add_executable(lab12_tests tests/test_resource_management.cpp)
target_link_libraries(lab12_tests PRIVATE lab12_lib GTest::gtest_main)
target_compile_features(lab12_tests PRIVATE cxx_std_20)
include(GoogleTest)
gtest_discover_tests(lab12_tests)
