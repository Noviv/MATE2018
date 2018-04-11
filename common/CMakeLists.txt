cmake_minimum_required(VERSION 3.1)

project(common)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(Boost REQUIRED system)

file(GLOB common_SRC src/*.cpp)
add_library(common ${common_SRC})
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
