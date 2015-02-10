cmake_minimum_required (VERSION 2.8)
project (LeapMusic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -Wextra")

set (LeapMusic_VERSION_MAJOR 0)
set (LeapMusic_VERSION_MINOR 1)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include (cmake/TargetArch.cmake)
target_architecture (arch)
message (STATUS "Architecture is ${arch}")

set (Leap_lib ${CMAKE_SOURCE_DIR}/LeapSDK/lib)
find_package(PortAudio)

add_subdirectory (src)
