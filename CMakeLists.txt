cmake_minimum_required(VERSION 3.20)
project(assignment1)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

file(GLOB RESOURCES "resources/*.map")
file(GLOB HEADERS "src/**/*.h")
file(GLOB SOURCES "src/**/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX ".+Driver.cpp")

add_library(AssignmentLib STATIC ${SOURCES} ${HEADERS} ${RESOURCES})

add_executable(OrdersDriver ${PROJECT_SOURCE_DIR}/src/Orders/OrdersDriver.cpp)
target_link_libraries(OrdersDriver AssignmentLib)

add_executable(PlayerDriver ${PROJECT_SOURCE_DIR}/src/Player/PlayerDriver.cpp)
target_link_libraries(PlayerDriver AssignmentLib)
