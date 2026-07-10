cmake_minimum_required(VERSION 3.14)
project(lab10_function_templates LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)


add_library(route_utils INTERFACE)
target_include_directories(route_utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(lab10_main main.cpp)
target_link_libraries(lab10_main PRIVATE route_utils)

add_executable(lab10_tests tests/test_route_utils.cpp)
target_link_libraries(lab10_tests PRIVATE route_utils GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab10_tests)
