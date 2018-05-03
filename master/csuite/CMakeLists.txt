cmake_minimum_required(VERSION 3.1)

project(csuite)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

file(GLOB_RECURSE csuite_SRC src/*.cpp)
include_directories(include)
add_executable(csuite_main ${csuite_SRC})
qt5_use_modules(csuite_main Widgets)

file(GLOB csuite_H include/*.hpp)
set(csuite_FORMATTABLE "${csuite_H};${csuite_SRC}" CACHE INTERNAL "csuite formattable files")
