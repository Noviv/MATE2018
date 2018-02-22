project(GUI)

add_custom_target(GUI ALL DEPENDS GUI COMMAND python3 -m py_compile dive_comp.py)

get_directory_property(clean_files ADDITIONAL_MAKE_CLEAN_FILES)
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
	"${clean_files};dive_comp.pyc;__pycache__")
