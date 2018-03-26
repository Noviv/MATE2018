cmake_minimum_required(VERSION 3.1)

project(GUI)

add_custom_target(GUI ALL
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMAND python3 -m py_compile dive_comp.py
	COMMAND rm -rf __pycache__
	COMMAND rm -rf dive_comp.pyc
)
