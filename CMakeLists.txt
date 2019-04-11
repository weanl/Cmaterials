cmake_minimum_required(VERSION 3.12)
project(Cmaterials)

set(CMAKE_CXX_STANDARD 14)

include_directories(Exa1_multithread)

add_executable(Cmaterials
        Exa1_multithread/exa1.cpp
        Exa1_multithread/exa1.h
        Exa2_/exa2.cpp
        Cmaterials.cpp)
