cmake_minimum_required(VERSION 2.8)
project(primefactors)
add_definitions(-std=c++11)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp primeFactorComputer.h)
add_executable(computeprimefactors ${SOURCE_FILES})