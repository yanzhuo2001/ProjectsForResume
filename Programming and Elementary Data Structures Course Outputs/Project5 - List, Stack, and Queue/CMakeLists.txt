cmake_minimum_required(VERSION 3.22)
project(Project5)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project5 main.cpp Dlist.h DlistImpl.h ../../p5/Instr.h Instr.h)
