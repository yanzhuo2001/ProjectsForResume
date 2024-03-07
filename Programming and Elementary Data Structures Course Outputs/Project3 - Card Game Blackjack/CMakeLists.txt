cmake_minimum_required(VERSION 3.22)
project(Project3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project3 blackjack.cpp deck.cpp deck.h card.cpp card.h hand.cpp hand.h player.cpp player.h rand.cpp rand.h)
