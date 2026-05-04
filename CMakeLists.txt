cmake_minimum_required(VERSION 3.14)
project(lab09_multiple_inheritance LANGUAGES CXX)

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

add_library(doc9_lib
    private/Document.cpp
    private/Printable.cpp
    private/Shareable.cpp
    private/Trackable.cpp
    private/ManagedDocument.cpp
)
target_include_directories(doc9_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)

add_executable(lab09_main main.cpp)
target_link_libraries(lab09_main PRIVATE doc9_lib)

add_executable(lab09_tests tests/test_managed_doc.cpp)
target_link_libraries(lab09_tests PRIVATE doc9_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab09_tests)
