cmake_minimum_required(VERSION 3.17)
project(Code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Code
        Algorithm.h
        FileRead.cpp
        FileRead.h
        FileWrite.cpp
        FileWrite.h
        main.cpp
        Search.cpp
        Search.h
        SearchAlgorithms.cpp
        SearchAlgorithms.h
        Sort.cpp
        Sort.h
        SortAlgorithms.cpp
        SortAlgorithms.h
        TSP.cpp
        TSP.h)
