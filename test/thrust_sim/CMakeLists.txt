cmake_minimum_required(VERSION 2.8)

project(thrust_sim)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(thrust_sim main.cpp)
target_link_libraries(thrust_sim ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
