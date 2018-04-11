cmake_minimum_required(VERSION 3.1)

project(MATE)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MATE_BINARY_DIR}/bin)

add_subdirectory(common)

find_path(BCMHOST bcm_host.h PATHS /opt/vc/include)
if(NOT BCMHOST)
	add_subdirectory(master)
endif()

add_subdirectory(slave)
