cmake_minimum_required(VERSION 3.22)
project(decompress)

set(CMAKE_CXX_STANDARD 20)

add_executable(decompress
        main.cpp
        Scanner.h
        Token.h)
