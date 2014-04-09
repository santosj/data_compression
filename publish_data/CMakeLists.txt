cmake_minimum_required(VERSION 2.8.3)
project(publish_data)

find_package(catkin REQUIRED COMPONENTS roscpp rospy sensor_msgs tf genmsg)

## Generate added messages and services
generate_messages(DEPENDENCIES sensor_msgs tf)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(publish_data src/publish_data.cpp)
target_link_libraries(publish_data ${catkin_LIBRARIES})

