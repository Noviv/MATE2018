cmake_minimum_required(VERSION 3.1)

project(wip)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

include_directories(
	${Common_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
)

add_executable(wip_img_serv serv.cpp)
target_link_libraries(wip_img_serv
	${Common_LIBS}
	${OpenCV_LIBS}
	${CMAKE_THREAD_LIBS_INIT}
)

add_executable(wip_img_recv recv.cpp)
target_link_libraries(wip_img_recv
	${Common_LIBS}
	${OpenCV_LIBS}
	${CMAKE_THREAD_LIBS_INIT}
)
