cmake_minimum_required(VERSION 3.10)
project(ArrayTestProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(runTests test.cpp array.cpp)
