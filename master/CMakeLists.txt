cmake_minimum_required(VERSION 3.1)

project(master)

add_subdirectory(csuite)
add_subdirectory(csys)
add_subdirectory(GUI)
add_subdirectory(test)

set(master_FORMATTABLE "${csuite_FORMATTABLE};${csys_FORMATTABLE};${GUI_FORMATTABLE};${test_FORMATTABLE}" CACHE INTERNAL "master formattable files")
