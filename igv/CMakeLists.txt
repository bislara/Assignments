cmake_minimum_required(VERSION 2.8.3)
project(igv)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  genmsg
)
find_package(OpenCV REQUIRED)

add_message_files( FILES drivedata.msg )

generate_messages( DEPENDENCIES std_msgs )

catkin_package(CATKIN_DEPENDS message_runtime)

include_directories( include  ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} )

add_executable(driver src/driver.cpp)
target_link_libraries(driver ${catkin_LIBRARIES} ${OpenCV_LIBS})
add_dependencies(driver igv_generate_messages_cpp)

