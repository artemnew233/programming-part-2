cmake_minimum_required(VERSION 3.20)
project(lab18_ci_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Enable ASan and UBSan" OFF)

function(enable_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /WX)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endfunction()

function(enable_sanitizers target)
    if(ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(${target} PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer)
        target_link_options(${target} PRIVATE -fsanitize=address,undefined)
    endif()
endfunction()

add_library(lab18 src/route.cpp)
target_include_directories(lab18 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
enable_warnings(lab18)
enable_sanitizers(lab18)

add_executable(lab18_demo src/main.cpp)
target_link_libraries(lab18_demo PRIVATE lab18)
enable_warnings(lab18_demo)
enable_sanitizers(lab18_demo)

include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(lab18_tests tests/route_tests.cpp)
target_link_libraries(lab18_tests PRIVATE lab18 GTest::gtest_main)
enable_warnings(lab18_tests)
enable_sanitizers(lab18_tests)

include(GoogleTest)
gtest_discover_tests(lab18_tests)
