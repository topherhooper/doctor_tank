cmake_minimum_required(VERSION 2.8.3)
project(ppigpio)

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
# set(PIGPIOD_IF2_SOURCES
#     src/pigpiod_if2.cpp)
# add_library(pigpiod_if2 ${PIGPIOD_IF2_SOURCES})

# libpigpiod_if2.so
# set(PIGPIOD_IF_SOURCES
#     src/pigpiod_if.cpp)
# add_library(pigpiod_if ${PIGPIOD_IF_SOURCES})

# libpigpiod_if2.so
set(PIGPIOD_IF2_SOURCES
    src/pigpio.cpp
    src/command.cpp
    src/pigpiod_if2.cpp)
add_library(pigpiod_if2 ${PIGPIOD_IF2_SOURCES})
target_link_libraries(pigpiod_if2
    ${CMAKE_THREAD_LIBS_INIT})

## Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)


