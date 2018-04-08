cmake_minimum_required(VERSION 3.1)

project(common)

set(common_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
	CACHE INTERNAL "common include dir" FORCE
)

add_library(common SHARED
	src/test.cpp
)
target_include_directories(common PUBLIC
	${common_INCLUDE_DIRS}
)
