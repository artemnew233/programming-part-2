cmake_minimum_required(VERSION 3.20)
project(lab01 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

find_package(fmt CONFIG REQUIRED)

add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(tests)
