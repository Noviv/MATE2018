cmake_minimum_required(VERSION 3.1)

project(MATE)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MATE_BINARY_DIR}/bin)

#add_subdirectory(common)
#add_subdirectory(wip)

#find_path(BCMHOST bcm_host.h PATHS /opt/vc/include)
#if(NOT BCMHOST)
#	add_subdirectory(master)
#endif()

#add_subdirectory(slave)

find_program(formatter clang-format)
find_program(formatter-6.0 clang-format-6.0)
if (formatter)
	set(FORMATTER "clang-format")
elseif(formatter-6.0)
	set(FORMATTER "clang-format-6.0")
endif()
find_program(checker cppcheck)
if (checker)
	set(CHECKER "cppcheck")
endif()

foreach(file ${common_FORMATTABLE};${slave_FORMATTABLE};${master_FORMATTABLE};${wip_FORMATTABLE})
	string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" file_name ${file})
	string(REPLACE . _ file_name ${file_name})
	string(REPLACE / _ file_name ${file_name})
	if (FORMATTER AND CHECKER)
		add_custom_target(cleanse_${file_name} ALL
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			COMMAND ${FORMATTER} -style=file -i ${file} && ${CHECKER} --enable=warning,performance,portability ${file}
			COMMENT "Cleansing ${file}..."
			VERBATIM
		)
	elseif(FORMATTER)
		add_custom_target(format_${file_name} ALL
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			COMMAND ${FORMATTER} -style=file -i ${file}
			COMMENT "Formatting ${file}..."
			VERBATIM
		)
	elseif(CHECKER)
		add_custom_target(check_${file_name} ALL
			COMMAND ${CHECKER} --enable=warning,performance,portability ${file}
			COMMENT "Checking ${file}..."
			VERBATIM
		)
	endif()
endforeach()
