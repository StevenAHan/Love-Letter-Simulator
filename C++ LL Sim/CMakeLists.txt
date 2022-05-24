cmake_minimum_required(VERSION 3.21)
project(C++ LL Sim)

set(CMAKE_CXX_STANDARD 14)

add_executable(LoveLetterSim main.cpp Card.cpp Card.h Deck.cpp Deck.h Player.cpp Player.h Game.cpp Game.h)
