cmake_minimum_required(VERSION 3.1)

project(navio)

set(CMAKE_CXX_STANDARD 11)
find_package(Boost REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS} Navio2/C++/Navio pigpio)

add_custom_target(
	pigpio
	COMMAND make
	WORKING_DIRECTORY pigpio
)

file(GLOB Navio2_SRC
	"Navio2/C++/Navio/Common/*.c"
	"Navio2/C++/Navio/Navio2/*.c"
	"Navio2/C++/Navio/Common/*.cpp"
	"Navio2/C++/Navio/Navio2/*.cpp"
)

add_library(Navio2 SHARED
	${Navio2_SRC}
)
target_include_directories(Navio2 PRIVATE pigpio)

add_executable(navio main.cpp)
target_link_libraries(navio
	${Boost_LIBRARIES}
	Navio2
	-LNavio2/C++/Navio/
	-lpthread
)
add_dependencies(navio pigpio)