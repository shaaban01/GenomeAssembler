#include <iostream>
#include <chrono> // include chrono library
#include "../include/kmerifier.h"
#include "../include/graph.h"
#include "../include/preprocessing.h"

int main()
{
    std::string filename = "../data/reads.txt";

    // Read genome reads from the file
    auto startReading = std::chrono::high_resolution_clock::now(); // start timer for file reading
    auto result = readGenomeReads(filename);
    auto endReading = std::chrono::high_resolution_clock::now(); // end timer for file reading

    // Access the vector of genome reads and the length of each read
    std::vector<std::string> genomeReads = result.first;
    int k = result.second;

    // Process the genome reads
    std::cout << "Done reading\n";

    auto start = std::chrono::high_resolution_clock::now(); // start timer for processing
    KMerifier kmerifier(k);
    std::cout << k << "-merifier created \n";
    kmerifier.TransformReadsToKmers(genomeReads);
    DeBruijnGraph graph(kmerifier);
    std::cout << "Eulerian path: " << graph.DoEulerianWalk() << "\n";
    auto end = std::chrono::high_resolution_clock::now(); // end timer for processing

    auto durationReading = std::chrono::duration_cast<std::chrono::microseconds>(endReading - startReading); // calculate duration for file reading in microseconds
    auto durationProcessing = std::chrono::duration_cast<std::chrono::microseconds>(end - start);            // calculate duration for processing in microseconds

    std::cout << "Time taken for file reading: " << durationReading.count() << " microseconds\n";  // print duration for file reading in microseconds
    std::cout << "Time taken for processing: " << durationProcessing.count() << " microseconds\n"; // print duration for processing in microseconds

    return 0;
}