# FILEPATH: /home/chaaban/code/CMPS/297/GenomeAssembler/CMakeLists.txt
# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)


# Name of the project
project(GenomeAssembler)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Add OpenMP flag to CMAKE_CXX_FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")



# Add source files to the project
add_executable(osama_assembler src/main.cpp src/kmerifier.cpp src/graph.cpp src/preproccessing.cpp)

add_executable(GenomeAssemblerTests tests/test_main.cpp)

find_package(GTest REQUIRED)

find_package(OpenMP REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(GenomeAssemblerTests ${GTEST_LIBRARIES})

# Link OpenMP library to your target
target_link_libraries(osama_assembler PUBLIC OpenMP::OpenMP_CXX)
