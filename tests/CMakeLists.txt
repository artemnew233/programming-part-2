add_executable(calculator_tests test_calculator.cpp)

target_link_libraries(calculator_tests PRIVATE calculator GTest::gtest_main)

target_compile_features(calculator_tests PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(calculator_tests)
