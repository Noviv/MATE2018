cmake_minimum_required(VERSION 3.1)

project(navio)

set(CMAKE_CXX_STANDARD 11)
find_package(Boost REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS} NavioLib)

add_executable(navio main.cpp)
target_link_libraries(navio
	${Boost_LIBRARIES}
	-LNavioLib
	-lnavio
	-lpthread)
