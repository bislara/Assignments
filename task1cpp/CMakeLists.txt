cmake_minimum_required(VERSION 2.8)
project(task1cpp)
find_package( OpenCV REQUIRED )
add_executable( task1cpp hsv.cpp )
target_link_libraries( task1cpp ${OpenCV_LIBS} )

