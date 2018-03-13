cmake_minimum_required(VERSION 3.5)

project(rein)

add_definitions("-Wall -std=c++11")

add_executable(test_Table test_Table.cpp Table.cpp)
add_executable(test_Combination test_Combination.cpp Combination.cpp)
add_executable(test_QLearn test_QLearn.cpp QLearn.cpp)
