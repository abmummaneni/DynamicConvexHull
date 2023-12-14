cmake_minimum_required(VERSION 3.26)
project(DynamicConvexHull)
set(CMAKE_CXX_STANDARD 23)


add_executable(DynamicConvexHull main.cpp
        ConcatenableQueue.h
        TTree.h
        TTree.cpp
        ConcatenableQueue.cpp
        Point.h
        Point.cpp
        Angle.cpp
        Angle.h
        VisUtils.cpp
        VisTTree.cpp
        VisTTree.h)

add_executable(timer timer.cpp
        ConcatenableQueue.h
        TTree.h
        TTree.cpp
        ConcatenableQueue.cpp
        Point.h
        Point.cpp
        Angle.cpp
        Angle.h)

add_executable(minimalLeda minimalLeda.cpp
        ConcatenableQueue.h
        TTree.h
        TTree.cpp
        ConcatenableQueue.cpp
        Point.h
        Point.cpp
        Angle.cpp
        Angle.h
        VisUtils.cpp
        VisUtils.h)

include_directories(/usr/local/include)
include_directories(/opt/homebrew/Cellar/matplotplusplus/1.2.0)
find_package(Matplot++ REQUIRED)
include_directories(${MATPLOT_INCLUDE_DIRS})

add_executable(randMatplot++ randMatplot++.cpp
        ConcatenableQueue.h
        TTree.h
        TTree.cpp
        ConcatenableQueue.cpp
        Point.h
        Point.cpp
        Angle.cpp
        Angle.h)
target_link_libraries(randMatplot++ Matplot++::matplot)
add_executable(mediumLeda VisTTree.cpp VisTTree.h
        mediumLeda.cpp)
