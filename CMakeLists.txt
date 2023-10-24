# FILEPATH: /home/chaaban/code/CMPS/297/GenomeAssembler/CMakeLists.txt
# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)


# Name of the project
project(GenomeAssembler)

# Set C++ standard to C++14
set(CMAKE_CXX_STANDARD 14)

# Add source files to the project
add_executable(GenomeAssembler src/main.cpp)

add_executable(GenomeAssemblerTests tests/test_main.cpp)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(GenomeAssemblerTests ${GTEST_LIBRARIES})
