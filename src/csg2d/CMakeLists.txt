cmake_minimum_required(VERSION 3.27)
project(cw11)

set(CMAKE_CXX_STANDARD 23)

add_executable(cw11 main.cpp functions.cpp functions.h libincludes.h operation.h shape.cpp shape.h
        circle.cpp
        circle.h
        rectangle.cpp
        rectangle.h
        complexShape.cpp
        complexShape.h)
