#include <iostream>
#include <chrono> // include chrono library
#include "../include/kmerifier.h"
#include "../include/graph.h"

int main()
{
    auto start = std::chrono::high_resolution_clock::now(); // start timer
    KMerifier kmerifier(5);
    std::vector<std::string> reads = {"AAGATTCTCTAAGA"};
    kmerifier.TransformReadsToKmers(reads);
    DeBruijnGraph graph(kmerifier);
    graph.printGraph();
    std::cout << "Eulerian path: " << graph.DoEulerianWalk() << std::endl;
    auto end = std::chrono::high_resolution_clock::now();                                        // end timer
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);          // calculate duration in microseconds
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl; // print duration in microseconds

    return 0;
}