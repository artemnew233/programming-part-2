cmake_minimum_required(VERSION 3.14)
project(lab08_abstract_polymorphism LANGUAGES CXX)

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

add_library(doc8_lib
    private/Document.cpp
    private/OfficialDocument.cpp
    private/Contract.cpp
    private/TechnicalDocument.cpp
)
target_include_directories(doc8_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)

add_executable(lab08_main main.cpp)
target_link_libraries(lab08_main PRIVATE doc8_lib)

add_executable(lab08_tests tests/test_polymorphism.cpp)
target_link_libraries(lab08_tests PRIVATE doc8_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab08_tests)
