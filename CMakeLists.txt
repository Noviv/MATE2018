cmake_minimum_required(VERSION 3.1)

project(MATE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MATE_SOURCE_DIR}/bin)

add_subdirectory(master)
add_subdirectory(slave)
