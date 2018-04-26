cmake_minimum_required(VERSION 3.1)

project(master)

add_subdirectory(csys)
add_subdirectory(test)
add_subdirectory(GUI)
add_subdirectory(csuite)

set(master_FORMATTABLE "${csys_FORMATTABLE};${test_FORMATTABLE};${GUI_FORMATTABLE};${csuite_FORMATTABLE}" CACHE INTERNAL "master formattable files")
