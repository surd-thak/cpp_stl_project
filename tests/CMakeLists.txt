# a new executable just for testing
add_executable(unit_tests 
    test_vector.cpp 
    test_map.cpp
)

# Link Google Test (gtest_main includes a default main function)
target_link_libraries(unit_tests GTest::gtest_main)

target_include_directories(unit_tests PRIVATE ../include)

include(GoogleTest)
gtest_discover_tests(unit_tests)