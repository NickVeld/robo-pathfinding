cmake_minimum_required(VERSION 3.8)
project(robo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES asearch.cpp astar.cpp config.cpp dijkstra.cpp environmentoptions.cpp isearch.cpp
        jp_search.cpp map.cpp mission.cpp theta.cpp tinyxml2.cpp xmllogger.cpp)
add_executable(robo ${SOURCE_FILES})