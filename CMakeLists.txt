cmake_minimum_required(VERSION 3.5)

project(rein)

add_definitions("-Wall -std=c++11")

set(SRC_DIR ./src)
set(INCLUDE_DIR ./include/rein)
include_directories(${INCLUDE_DIR})

add_library(rein STATIC ${SRC_DIR}/QLearn.cpp
						${SRC_DIR}/Table.cpp
						${SRC_DIR}/Combination.cpp
						)

install(TARGETS rein
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	)

install(
	DIRECTORY include/rein
	DESTINATION /usr/local/include
	)

#add_executable(test_Table test_Table.cpp Table.cpp)
#add_executable(test_Combination test_Combination.cpp Combination.cpp)
