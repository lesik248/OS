cmake_minimum_required(VERSION 3.10)
project(FactorialTestProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(runTests test.cpp FACTORIAL.cpp)
