cmake_minimum_required(VERSION 3.26)
project(DynamicConvexHull)

set(CMAKE_CXX_STANDARD 23)

add_executable(DynamicConvexHull main.cpp
        DynamicCH.h
        ConcatenableQueue.h
        TTree.h
        TTree.cpp
        ConcatenableQueue.cpp
        Point.h
        Point.cpp
        Angle.cpp
        Angle.h)
