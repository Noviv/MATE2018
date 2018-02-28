cmake_minimum_required(VERSION 3.1)

project(csys)

set(GCC_CXX_FLAGS "-O3 -Wall -Wpedantic")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED system)

file(GLOB_RECURSE SRC src/*.cpp)
include_directories(include/ ${Boost_INCLUDE_DIRS})

add_executable(csys ${SRC})
target_link_libraries(csys ${Boost_LIBRARIES} -lX11 -lm)
