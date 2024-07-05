cmake_minimum_required(VERSION 3.26)
project(ex3)

set(CMAKE_CXX_STANDARD 17)

add_executable(ex3 main.cpp
        Producer.cpp
        Dispatcher.cpp
        CoEditor.cpp
        BoundedBuffer.cpp
        ConfigReader.cpp
        ScreenManager.cpp
        UnboundedBuffer.cpp)
