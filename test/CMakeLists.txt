cmake_minimum_required(VERSION 3.5)

add_definitions("-std=c++11")

add_executable(test1 test.cpp)

target_link_libraries(test1 rein)
