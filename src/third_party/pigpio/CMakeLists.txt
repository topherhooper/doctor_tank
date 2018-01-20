cmake_minimum_required(VERSION 2.8.3)
project(pigpio)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)

find_package(catkin REQUIRED)
find_package(Threads REQUIRED)

catkin_package(
  INCLUDE_DIRS include
)

# Directories needed to install pigpio
include_directories(include)

# libpigpio.so
set(PIGPIO_SOURCES
    src/command.cpp
    src/pigpio.cpp)
add_library(pigpio ${PIGPIO_SOURCES})
target_link_libraries(pigpio
    ${CMAKE_THREAD_LIBS_INIT}
    rt)

# libpigpiod_if2.so
set(PIGPIOD_IF2_SOURCES
    src/command.cpp
    src/pigpiod_if2.cpp)
add_library(pigpiod_if2 ${PIGPIOD_IF2_SOURCES})
target_link_libraries(pigpiod_if2
    ${CMAKE_THREAD_LIBS_INIT}
    rt)

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)


