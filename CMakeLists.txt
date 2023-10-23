# FILEPATH: /home/chaaban/code/CMPS/297/GenomeAssembler/CMakeLists.txt
# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(GenomeAssembler)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Add source files to the project
add_executable(GenomeAssembler src/main.cpp)
