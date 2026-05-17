cmake_minimum_required(VERSION 3.14)
project(lab11_class_templates LANGUAGES CXX)

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

# All headers; no separate .cpp needed for templates
add_library(route_table_lib INTERFACE)
target_include_directories(route_table_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(lab11_main main.cpp)
target_link_libraries(lab11_main PRIVATE route_table_lib)

add_executable(lab11_tests tests/test_route_table.cpp)
target_link_libraries(lab11_tests PRIVATE route_table_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab11_tests)
