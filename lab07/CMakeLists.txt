cmake_minimum_required(VERSION 3.14)
project(lab07_inheritance LANGUAGES CXX)

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

add_library(doc_lib
    private/Document.cpp
    private/OfficialDocument.cpp
    private/Contract.cpp
    private/TechnicalDocument.cpp
)
target_include_directories(doc_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/public)

add_executable(lab07_main main.cpp)
target_link_libraries(lab07_main PRIVATE doc_lib)

add_executable(lab07_tests tests/test_documents.cpp)
target_link_libraries(lab07_tests PRIVATE doc_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab07_tests)
