
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(depth2PointCloud)

set(CMAKE_CXX_FLAGS "-std=c++11")
find_package(PCL 1.2 REQUIRED)
find_package(OpenCV 3.4 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIRS})

add_executable(depth2PointCloud main.cpp)
target_link_libraries(depth2PointCloud ${PCL_LIBRARIES})
target_link_libraries(depth2PointCloud ${OpenCV_LIBS})
