cmake_minimum_required(VERSION 3.1)

project(csys)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(Boost REQUIRED system unit_test_framework)

file(GLOB_RECURSE SRC src/*.cpp)
add_executable(csys_main ${SRC})
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

file(GLOB_RECURSE SRC_TEST test/*.cpp)
foreach(testsrc ${SRC_TEST})
	get_filename_component(testnm ${testsrc} NAME_WE)
	add_executable(${testnm} ${testsrc})
	target_include_directories(${testnm} PUBLIC include ${Boost_INCLUDE_DIRS})
	target_link_libraries(${testnm} ${Boost_LIBRARIES})
	add_test(NAME ${testnm} COMMAND ${testnm})
endforeach()
