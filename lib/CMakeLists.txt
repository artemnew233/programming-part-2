add_library(schedule src/schedule.cpp)

target_include_directories(schedule PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(schedule PUBLIC cxx_std_20)
