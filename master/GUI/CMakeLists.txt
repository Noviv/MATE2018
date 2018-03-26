cmake_minimum_required(VERSION 3.1)

project(GUI)

file(GLOB GUI_src
	"*.py"
)

add_custom_target(GUI
	COMMAND python3 -m py_compile ${GUI_src}
	OUTPUT dive_comp.pyc __pycache__
)
