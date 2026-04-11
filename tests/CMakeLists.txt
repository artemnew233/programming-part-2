add_executable(schedule_tests test_schedule.cpp)

target_link_libraries(schedule_tests PRIVATE schedule GTest::gtest_main)

target_compile_features(schedule_tests PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(schedule_tests)
