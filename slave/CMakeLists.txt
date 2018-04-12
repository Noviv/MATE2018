cmake_minimum_required(VERSION 3.1)

project(slave)

add_subdirectory(navio)

set(slave_FORMATTABLE "${navio_FORMATTABLE}" CACHE INTERNAL "slave formattable files")
