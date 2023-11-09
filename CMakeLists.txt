cmake_minimum_required(VERSION 3.26)
project(DynamicConvexHull)
set(CMAKE_CXX_STANDARD 23)
include_directories(/usr/local/include)
include_directories(/opt/homebrew/Cellar/matplotplusplus/1.2.0)
find_package(Matplot++ REQUIRED)
include_directories(${MATPLOT_INCLUDE_DIRS})



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

target_link_libraries(DynamicConvexHull Matplot++::matplot)
