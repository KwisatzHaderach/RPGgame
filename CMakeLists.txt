cmake_minimum_required(VERSION 3.3)
project(ZOO_game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Capsule.cpp City.cpp Finale.cpp GameEngine.cpp Hero.cpp
        Inventory.cpp Item.cpp main.cpp NPC.cpp Person.cpp Place.cpp
        BeginningPlace.cpp DeadEnd.cpp FinishingPlace.cpp variables.cpp)
add_executable(ZOO_game ${SOURCE_FILES})