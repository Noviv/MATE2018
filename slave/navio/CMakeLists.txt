cmake_minimum_required(VERSION 3.1)

project(navio)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(Boost REQUIRED system)
find_package(OpenCV REQUIRED)

file(GLOB pigpio_SRC
	"pigpio/pigpio.c"
	"pigpio/custom.cext"
	"pigpio/command.c"
)
add_library(pigpio SHARED
	${pigpio_SRC}
)
target_link_libraries(pigpio PUBLIC
	-lpthread
	-fpic
)
target_include_directories(pigpio PUBLIC
	pigpio
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
	${OpenCV_INCLUDE_DIRS}
	Navio2/C++/Navio
)
target_link_libraries(navio_main
	${Boost_LIBRARIES}
	${OpenCV_LIBS}
	pigpio
	NavioLib
	-lpthread
)
