cmake_minimum_required(VERSION 3.16)
project(ngohongs)

set(CMAKE_CXX_STANDARD 14)

add_executable(ngohongs src/main.cpp
                        src/CApplication.cpp src/CApplication.h
                        src/CGame.cpp src/CGame.h
                        src/CInterface.cpp src/CInterface.cpp
                        src/CCommand.h
                        src/CCommandHelp.cpp src/CCommandHelp.h
                        src/CCommandQuit.cpp src/CCommandQuit.h)