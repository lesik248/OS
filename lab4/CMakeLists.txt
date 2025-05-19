cmake_minimum_required(VERSION 3.10)
project(lab4)

# Установим стандарт C++98
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем исполняемый файл для Receiver
add_executable(receiver src/receiver.cpp)

# Добавляем исполняемый файл для Sender
add_executable(sender src/sender.cpp)

# Добавим нужную библиотеку Windows (обязательно для работы с WinAPI)
if(WIN32)
    target_link_libraries(receiver PRIVATE ws2_32)
    target_link_libraries(sender PRIVATE ws2_32)
endif()
