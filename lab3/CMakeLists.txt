cmake_minimum_required(VERSION 3.10)
project(MarkerTests CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
endif()

set(SOURCES
        src/marker_utils.cpp
)

# Основная программа
add_executable(main_program
        src/main.cpp
        ${SOURCES}
)

# Тесты
add_executable(tests
        tests/catch_main.cpp
        tests/test_marker_utils.cpp
        ${SOURCES}
)

enable_testing()
add_test(NAME CatchTests COMMAND tests)
