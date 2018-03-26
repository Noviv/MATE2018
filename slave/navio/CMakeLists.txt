cmake_minimum_required(VERSION 3.1)

project(navio)

set(CMAKE_CXX_STANDARD 11)
find_package(Boost REQUIRED system)

add_custom_target(pigpio
	COMMAND make
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pigpio
)

add_custom_target(cleanfull
	COMMAND cd ${CMAKE_CURRENT_BINARY_DIR} && make clean
	COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/pigpio && make clean
)

file(GLOB NavioLib_SRC
	"Navio2/C++/Navio/Common/*.cpp"
	"Navio2/C++/Navio/Navio2/*.cpp"
)
add_library(NavioLib SHARED
	${NavioLib_SRC}
)
target_include_directories(NavioLib PUBLIC
	Navio2/C++/Navio/
	pigpio
)

file(GLOB Navio_SRC
	"src/*.cpp"
)
add_executable(navio_main ${Navio_SRC})
target_include_directories(navio_main PUBLIC
	include
	${Boost_INCLUDE_DIRS}
	Navio2/C++/Navio
)
target_link_libraries(navio_main
	${Boost_LIBRARIES}
	NavioLib
	-LNavio2/C++/Navio/
	-lpthread
)
add_dependencies(navio_main pigpio)
