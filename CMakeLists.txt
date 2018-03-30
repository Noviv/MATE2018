cmake_minimum_required(VERSION 3.1)

project(MATE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MATE_BINARY_DIR}/bin)

if(NOT IS_RASP)
	message(WARNINGS master)
	add_subdirectory(master)
endif()

add_subdirectory(slave)
