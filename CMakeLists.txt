cmake_minimum_required(VERSION 3.21)
project(IDATT2104___Network_Programming)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(IDATT2104___Network_Programming
        p2d/p2.cpp p5d/Compiler.cpp p5d/Compiler.h p5d/Compile/DockerFile)
