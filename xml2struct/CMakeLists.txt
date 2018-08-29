cmake_minimum_required(VERSION 3.2)
project(test_pug)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CXX_FLAGS -std=c++0x -g)
string (REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")


add_executable(test_pug main.cpp pugixml.cpp)
