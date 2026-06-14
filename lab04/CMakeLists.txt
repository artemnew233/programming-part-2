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

add_library(movieticket src/MovieTicket.cpp)
target_include_directories(movieticket PUBLIC include)
target_compile_features(movieticket PUBLIC cxx_std_20)
if(MSVC)
    target_compile_options(movieticket PRIVATE /W4)
else()
    target_compile_options(movieticket PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(lab04_app src/main.cpp)
target_link_libraries(lab04_app PRIVATE movieticket)

add_executable(lab04_tests tests/test_movieticket.cpp)
target_link_libraries(lab04_tests PRIVATE movieticket GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab04_tests)
