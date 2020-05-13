cmake_minimum_required(VERSION 3.16)
project(ngohongs)

set(CMAKE_CXX_STANDARD 14)

add_executable(ngohongs src/main.cpp src/CApplication.cpp src/CGame.cpp src/CInterface.cpp src/CCommandQuit.cpp src/CCommandQuit.h)