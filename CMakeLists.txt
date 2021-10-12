cmake_minimum_required(VERSION 3.17)
project(assignment1)

set(CMAKE_CXX_STANDARD 14)

add_executable(assignment1
        TestDriver.cpp TestDriver.h
        Player/Player.cpp Player/Player.h Player/PlayerDriver.cpp
        Orders/Orders.cpp Orders/Orders.h Orders/OrdersDriver.cpp
        Map/Map.cpp Map/Map.h GameEngine/GameEngine.cpp GameEngine/GameEngine.h)