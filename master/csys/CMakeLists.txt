cmake_minimum_required(VERSION 3.1)

project(csys)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(Boost REQUIRED system)

file(GLOB_RECURSE SRC src/*.cpp)

add_executable(csys_main ${SRC})
target_include_directories(csys_main PUBLIC
	include ${common_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS}
)
target_link_libraries(csys_main
	common ${Boost_LIBRARIES} -lX11 -lm
)
