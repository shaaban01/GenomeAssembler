#include <iostream>

int main(int argc, char **argv)
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}

// Just to have an Idea of how this code be implemented -- THIS IS NOT THE FINAL CODE

// #include <iostream>
// #include "preprocessing.h"
// #include "graph.h"
// #include "contig.h"

// int main() {
// Step 1: Read and preprocess input data
//     std::string inputFileName = "input.fasta";  // Replace with your actual input file
//     std::string outputFileName = "output.fasta";  // Replace with your desired output file

//     Preprocessing preprocessing;
//     if (preprocessing.loadInputData(inputFileName)) {
//         preprocessing.performQualityControl();
//         preprocessing.performErrorCorrection();
//         preprocessing.saveProcessedData("preprocessed_data.fasta");
//     } else {
//         std::cerr << "Error loading input data." << std::endl;
//         return 1;  // Exit with an error code
//     }

// Step 2: Construct the De Bruijn graph
//     DeBruijnGraph deBruijnGraph;
//     deBruijnGraph.constructGraph(preprocessing.getProcessedData());

// Step 3: Simplify the graph
//     deBruijnGraph.simplifyGraph(); -- this might include the eularin path algorithm or other algorithms

// Step 4: Generate contigs
//     ContigGeneration contigGeneration;
//     contigGeneration.generateContigs(deBruijnGraph);

// Step 5: Save assembled contigs to the output file
//     contigGeneration.saveContigs(outputFileName);

//     std::cout << "Assembly completed successfully." << std::endl;
//     return 0;  // Exit with a success code
// }
