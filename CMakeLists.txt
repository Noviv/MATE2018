cmake_minimum_required(VERSION 3.1)

project(MATE)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MATE_BINARY_DIR}/bin)

add_subdirectory(common)

find_path(BCMHOST bcm_host.h PATHS /opt/vc/include)
if(NOT BCMHOST)
	add_subdirectory(master)
endif()

add_subdirectory(slave)

find_program(formatter clang-format)
find_program(checker cppcheck)

foreach(file ${common_FORMATTABLE};${slave_FORMATTABLE};${master_FORMATTABLE})
	string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" file_name ${file})
	string(REPLACE . _ file_name ${file_name})
	string(REPLACE / _ file_name ${file_name})
	if (formatter AND checker)
		add_custom_target(format_${file_name} ALL
			COMMAND clang-format -i ${file} && cppcheck ${file} --enable=warning,performance,portability
			COMMENT "Cleansing ${file}..."
			VERBATIM
		)
	elseif(formatter)
		add_custom_target(format_${file_name} ALL
			COMMAND clang-format -i ${file}
			COMMENT "Formatting ${file}..."
			VERBATIM
		)
	elseif(checker)
		add_custom_target(format_${file_name} ALL
			COMMAND cppcheck ${file} --enable=warning,performance,portability
			COMMENT "Checking ${file}..."
			VERBATIM
		)
	endif()
endforeach()
