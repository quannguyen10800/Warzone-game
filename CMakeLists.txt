cmake_minimum_required(VERSION 3.20)
project(Local_COMP345)

set(CMAKE_CXX_STANDARD 17)

add_executable(Local_COMP345 main.cpp LoggingObserver/LoggingObserver.h LoggingObserver/LoggingObserver.cpp)
