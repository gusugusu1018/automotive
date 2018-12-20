cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(show)

set(CMAKE_CXX_FLAGS "-std=c++11")
find_package(OpenCV 3.3 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIRS})

add_executable(show main.cpp)
target_link_libraries(show ${OpenCV_LIBS})
