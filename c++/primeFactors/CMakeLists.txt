cmake_minimum_required(VERSION 3.6)
project(projects)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp primeFactorComputer.h)
add_executable(projects ${SOURCE_FILES})