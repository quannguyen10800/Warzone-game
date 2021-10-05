cmake_minimum_required(VERSION 3.20)
project(assignment1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 14)

add_library(assignment1 library.cpp)


add_executable(OrdersDriver ${PROJECT_SOURCE_DIR}/src/Orders/OrdersDriver.cpp)
target_link_libraries(OrdersDriver assignment1)

