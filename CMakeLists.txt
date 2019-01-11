cmake_minimum_required(VERSION 3.13)
project(MethodsOfOptimization)

set(CMAKE_CXX_STANDARD 17)

add_executable(MethodsOfOptimization main.cpp GradientMethod.cpp GradientMethod.h Gnuplot.h Color.h)