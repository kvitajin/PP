cmake_minimum_required(VERSION 3.17)
project(omp LANGUAGES CXX)

find_library(OpenMP REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fopenmp")

set(CMAKE_CXX_STANDARD 14)

add_executable(omp main.cpp)