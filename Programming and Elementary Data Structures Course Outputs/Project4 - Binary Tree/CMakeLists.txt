cmake_minimum_required(VERSION 3.22)
project(Project4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project4 binaryTree.cpp binaryTree.h huffmanTree.cpp huffmanTree.h compress.cpp decompress.cpp)
