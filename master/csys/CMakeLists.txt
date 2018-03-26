cmake_minimum_required(VERSION 3.1)

project(csys)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(Boost REQUIRED system)

file(GLOB_RECURSE SRC src/*.cpp)
include_directories(include/ ${Boost_INCLUDE_DIRS})

add_executable(csys_main ${SRC})
target_link_libraries(csys_main ${Boost_LIBRARIES} -lX11 -lm)
