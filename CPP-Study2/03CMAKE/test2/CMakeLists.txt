cmake_minimum_required(VERSION 2.8)

project(MultipleFileCompilation)

include_directories(./include)

add_executable(swap main.cpp src/swap.cpp)