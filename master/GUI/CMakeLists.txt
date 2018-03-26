cmake_minimum_required(VERSION 3.1)

project(GUI)

add_custom_command(
	OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dive_comp.py
	DEPENDS dive_comp.py
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMAND python3 -m py_compile dive_comp.py
	COMMAND rm -rf __pycache__
	COMMAND rm -rf dive_comp.pyc
	COMMAND cp dive_comp.py ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
	COMMENT "Validating GUI files"
	VERBATIM
)

add_custom_target(phony ALL DEPENDS dive_comp.py)
