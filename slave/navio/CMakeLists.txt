cmake_minimum_required(VERSION 3.1)

project(navio)

set(CMAKE_CXX_STANDARD 11)
find_package(Boost REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS} Navio2/C++/Navio)

add_custom_target(
	pigpio
	COMMAND make
	WORKING_DIRECTORY pigpio
)

add_executable(navio main.cpp)
target_link_libraries(
	navio
	${Boost_LIBRARIES}
	-LNavio2/C++/Navio/
	-lnavio
	-lpthread
)
add_dependencies(navio pigpio)
