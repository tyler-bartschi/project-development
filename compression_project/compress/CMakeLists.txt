cmake_minimum_required(VERSION 3.22)
project(compress)

set(CMAKE_CXX_STANDARD 20)

add_executable(compress
    main.cpp
        Token.h
        Scanner.h
        Parser.h
        Tuple.h
        Heap.h
        test_heap/test-heap.cpp)
