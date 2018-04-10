cmake_minimum_required(VERSION 3.1)

project(img_recv)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(Boost REQUIRED system serialization)
find_package(OpenCV REQUIRED)

file(GLOB img_recv_SRC
	"src/*.cpp"
)
add_executable(img_recv_main ${img_recv_SRC})
target_include_directories(img_recv_main PUBLIC
	include ${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(img_recv_main
	${Boost_LIBRARIES} ${OpenCV_LIBS}
)
