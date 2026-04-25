cmake_minimum_required(VERSION 3.14)
project(lab06_tree_composition LANGUAGES CXX)

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

add_library(tree_lib
    private/Fruit.cpp
    private/Leaf.cpp
    private/Branch.cpp
    private/Root.cpp
    private/Tree.cpp
)
target_include_directories(tree_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)

add_executable(lab06_main main.cpp)
target_link_libraries(lab06_main PRIVATE tree_lib)

add_executable(lab06_tests tests/test_tree.cpp)
target_link_libraries(lab06_tests PRIVATE tree_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab06_tests)
