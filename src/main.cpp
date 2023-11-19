#include <iostream>
#include <chrono> // include chrono library
#include "../include/kmerifier.h"
#include "../include/graph.h"
#include "../include/preprocessing.h"

int main(int argc, char *argv[])
{

    std::string filename = argv[1];

    // Read genome reads from the file
    auto startReading = std::chrono::high_resolution_clock::now(); // start timer for file reading
    auto result = readGenomeReads(filename);
    auto endReading = std::chrono::high_resolution_clock::now(); // end timer for file reading

    // Access the vector of genome reads and the length of each read
    std::vector<std::string> genomeReads = result.first;
    int k = result.second;

    // Process the genome reads
    std::cout << "Done reading\n";

    k = (k > 11) ? k - 5 : k;

    auto durationReading = std::chrono::duration_cast<std::chrono::microseconds>(endReading - startReading); // calculate duration for file reading in microseconds

    auto start = std::chrono::high_resolution_clock::now(); // start timer for processing
    KMerifier kmerifier(k);
    std::cout << k << "-merifier created \n";
    kmerifier.TransformReadsToKmers(genomeReads);
    DeBruijnGraph graph(kmerifier);

    std::ofstream outputFile;
    outputFile.open("../data/output.txt");
    outputFile << graph.DoEulerianWalk();
    auto end = std::chrono::high_resolution_clock::now(); // end timer for processing

    auto durationProcessing = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // calculate duration for processing in microseconds

    std::cout << "Time taken for file reading: " << durationReading.count() << " microseconds\n";  // print duration for file reading in microseconds
    std::cout << "Time taken for processing: " << durationProcessing.count() << " microseconds\n"; // print duration for processing in microseconds

    return 0;
}