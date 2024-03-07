cmake_minimum_required(VERSION 3.22)
project(main)

set(CMAKE_CXX_STANDARD 14)

add_executable(main mip.cpp constants.h image.h ppm.cpp)
