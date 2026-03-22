cmake_minimum_required(VERSION 3.20)
project(lab04 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(student src/Student.cpp)
target_include_directories(student PUBLIC include)
target_compile_features(student PUBLIC cxx_std_20)

add_executable(lab04_app src/main.cpp)
target_link_libraries(lab04_app PRIVATE student)

add_executable(lab04_tests tests/test_student.cpp)
target_link_libraries(lab04_tests PRIVATE student GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab04_tests)
