cmake_minimum_required(VERSION 3.1)

project(csys)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(Boost REQUIRED system unit_test_framework)

file(GLOB_RECURSE csys_SRC src/*.cpp)
add_executable(csys_main ${csys_SRC})
target_include_directories(csys_main PUBLIC
	${Boost_INCLUDE_DIRS}
	${Common_INCLUDE_DIRS}
	include
)
target_link_libraries(csys_main
	${Boost_LIBRARIES}
	${Common_LIBS}
	-lX11
	-lm
)

file(GLOB csys_H include/*.hpp)
set(csys_FORMATTABLE "${csys_SRC};${csys_H}" CACHE INTERNAL "csys formattable files")
