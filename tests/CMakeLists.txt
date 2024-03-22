enable_testing()
add_executable(emulator_test main_test.cpp ../src/emulator.cpp ../src/parser.cpp)
target_link_libraries(emulator_test gtest_main gmock_main)