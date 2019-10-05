cmake_minimum_required (VERSION 3.0)

set (CMAKE_CXX_FLAGS "-Wall -ansi")

project (Test)

add_executable(Test.e main.cpp pila.cpp)