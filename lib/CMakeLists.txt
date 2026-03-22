add_library(calculator src/calculator.cpp)

target_include_directories(calculator PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(calculator PUBLIC cxx_std_20)
