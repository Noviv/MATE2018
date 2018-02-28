cmake_minimum_required(VERSION 3.1)

project(thrust_sim)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost REQUIRED system)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${OPENGL_INCLUDE_DIRS}
	${GLFW_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS})

link_libraries(${GLEW_LIBRARIES})
add_executable(thrust_sim main.cpp)
target_link_libraries(thrust_sim
	${OPENGL_LIBRARIES}
	${GLFW_LIBRARIES}
	${GLEW_LIBRARIES}
	${Boost_LIBRARIES}
	-lGL
	-lGLU
	-lX11
	-lXxf86vm
	-lXrandr
	-lpthread
	-lXi
	-ldl
	-lm)
