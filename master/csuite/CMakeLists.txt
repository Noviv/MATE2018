cmake_minimum_required(VERSION 3.1)

project(csuite)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

file(GLOB_RECURSE source src/*.cpp)
include_directories(src)

add_executable(csuite_main src/main.cpp ${source})
qt5_use_modules(csuite_main Widgets)
