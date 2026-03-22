add_executable(app main.cpp)

target_link_libraries(app PRIVATE calculator fmt::fmt)

target_compile_features(app PRIVATE cxx_std_20)
