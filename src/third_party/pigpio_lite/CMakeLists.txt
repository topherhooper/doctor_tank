cmake_minimum_required(VERSION 2.8.3)
project(pigpio_lite)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)

find_package(catkin REQUIRED)

catkin_package(
  INCLUDE_DIRS include
)

# Directories needed to install pigpio
include_directories(include)

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)

