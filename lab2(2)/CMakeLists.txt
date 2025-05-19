cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab2)

add_executable(main_program
        main_program/main.cpp
        main_program/thread_utils.cpp
)

# Тесты
add_executable(tests
        tests/test_threads.cpp
        main_program/thread_utils.cpp
        tests/catch_main.cpp
)

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)