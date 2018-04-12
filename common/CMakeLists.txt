cmake_minimum_required(VERSION 3.1)

project(common)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(Boost REQUIRED system unit_test_framework)

add_library(common src/touch.cpp)
target_include_directories(common PUBLIC
	include ${Boost_INCLUDE_DIRS}
)
target_link_libraries(common
	${Boost_LIBRARIES}
)

set(Common_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
	CACHE STRING "common include dirs"
)
set(Common_LIBS "common"
	CACHE STRING "common libs"
)

file(GLOB_RECURSE SRC_TEST test/*.cpp)
foreach(testsrc ${SRC_TEST})
	get_filename_component(testnm ${testsrc} NAME_WE)
	add_executable(${testnm} ${testsrc})
	target_include_directories(${testnm} PUBLIC include ${Boost_INCLUDE_DIRS})
	target_link_libraries(${testnm} ${Boost_LIBRARIES})
	add_test(NAME ${testnm} COMMAND ${testnm})
endforeach()
