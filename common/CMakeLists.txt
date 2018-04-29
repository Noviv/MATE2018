cmake_minimum_required(VERSION 3.1)

project(common)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(Boost REQUIRED system unit_test_framework)

file(GLOB common_H "include/common/*.hpp" "include/common_wip/*.hpp")
add_library(common INTERFACE)
target_sources(common INTERFACE ${common_H})
target_include_directories(common INTERFACE
	include ${Boost_INCLUDE_DIRS}
)
target_link_libraries(common INTERFACE
	${Boost_LIBRARIES}
)

set(Common_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
	CACHE STRING "common include dirs"
)
set(Common_LIBS "common"
	CACHE STRING "common libs"
)

file(GLOB_RECURSE test_SRC test/*.cpp)
foreach(testsrc ${test_SRC})
	get_filename_component(testnm ${testsrc} NAME_WE)
	add_executable(${testnm} ${testsrc})
	target_include_directories(${testnm} PUBLIC include ${Boost_INCLUDE_DIRS})
	target_link_libraries(${testnm} ${Boost_LIBRARIES} -lm -lpthread)
	add_test(NAME ${testnm} COMMAND ${testnm})
endforeach()

set(common_FORMATTABLE "${common_H};${test_SRC}" CACHE INTERNAL "common formattable files")
