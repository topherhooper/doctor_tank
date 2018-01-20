cmake_minimum_required(VERSION 2.8.3)
project(buzzer)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)

# Find dependencies and load their CMake variables
find_package(catkin REQUIRED COMPONENTS pigpio)
# find_package(pigpio REQUIRED)
find_package(Threads REQUIRED)

# Define this as a catkin package
catkin_package(
    CATKIN_DEPENDS pigpio
    DEPENDS pigpio
)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include ${catkin_INCLUDE_DIRS})

# Buzz basic executable
add_executable(buzz_basic src/buzz.cpp)
target_link_libraries(buzz_basic
    pigpiod_if2
    ${catkin_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    rt
)
