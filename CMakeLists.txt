cmake_minimum_required(VERSION 3.10)
project(MatrixFigures)

set(CMAKE_CXX_STANDARD 14)

add_executable(MatrixFigures test.cpp Grid.h MatrixFigure.h MatrixFigure.cpp)
