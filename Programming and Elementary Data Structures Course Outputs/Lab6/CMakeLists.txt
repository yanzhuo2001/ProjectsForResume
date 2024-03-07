cmake_minimum_required(VERSION 3.22)
project(Lab6)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(plugins)

add_executable(Lab6
        plugins/cat/cat.cpp
        plugins/simple/simple.cpp
        plugins/cat.so
        plugins/simple.so
        main.cpp
        plugin.h
        pluginManager.cpp
        pluginManager.h
        prompt.h plugins/add/add.cpp plugins/styled/styled.cpp)
