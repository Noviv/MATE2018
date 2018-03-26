cmake_minimum_required(VERSION 3.1)

project(navio)

set(CMAKE_CXX_STANDARD 11)
find_package(Boost REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS} Navio2/C++/Navio pigpio include)

add_custom_target(
	pigpio
	COMMAND make
	WORKING_DIRECTORY pigpio
)

file(GLOB Navio_SRC
	"src/*.cpp"
)

file(GLOB NavioLib_SRC
	"Navio2/C++/Navio/Common/*.c"
	"Navio2/C++/Navio/Navio2/*.c"
	"Navio2/C++/Navio/Common/*.cpp"
	"Navio2/C++/Navio/Navio2/*.cpp"
)

add_library(NavioLib SHARED
	${NavioLib_SRC}
)

add_executable(navio_main ${Navio_SRC})
target_link_libraries(navio_main
	${Boost_LIBRARIES}
	NavioLib
	-LNavio2/C++/Navio/
	-lpthread
)
add_dependencies(navio_main pigpio)
