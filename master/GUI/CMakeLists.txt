cmake_minimum_required(VERSION 3.1)

project(GUI)

file(GLOB GUI_src
	"*.py"
)

add_custom_target(GUI
	COMMAND python3 -m py_compile ${GUI_src}
)

get_directory_property(clean_files ADDITIONAL_MAKE_CLEAN_FILES)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
	"${clean_files};dive_comp.pyc;__pycache__")
