cmake_minimum_required(VERSION 3.10.0)
project(Stack)
include(CTest)
enable_testing()

add_executable(stack main.cpp)
set_property(TARGET stack PROPERTY CXX_STANDARD_REQUIRED 17)
set_property(TARGET stack PROPERTY CXX_STANDARD 17)
add_test(NAME TEST COMMAND $<TARGET_FILE:stack>)