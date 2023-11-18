#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/preprocessing.h"

std::pair<std::vector<std::string>, int> readGenomeReads(const std::string& filename) {
    std::ifstream inputFile(filename);

    // Check if the file is opened successfully
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return {{}, 0}; // Return an empty vector and 0 length
    }

    // Read the first genome read from the file
    std::string firstGenomeRead;
    if (std::getline(inputFile, firstGenomeRead)) {
        // Get the length of the genome from the first read
        const int genomeLength = firstGenomeRead.length();

        // Display the length of the genome
        std::cout << "Genome Length: " << genomeLength << std::endl;

        // Reset the file pointer to the beginning of the file for subsequent reads
        inputFile.clear();
        inputFile.seekg(0, std::ios::beg);

        // Read and store the rest of the genome reads
        std::vector<std::string> genomeReads;
        std::string genomeRead;
        while (std::getline(inputFile, genomeRead)) {
            // Check if the read has the expected length
            if (genomeRead.length() == genomeLength) {
                // Store the genome read in the vector
                genomeReads.push_back(genomeRead);
            } else {
                std::cerr << "Error: Genome read does not have the expected length." << std::endl;
                // You might want to handle this error case differently based on your requirements
            }
        }

        // Close the file
        inputFile.close();

        // Return the vector of genome reads and the length of each read
        return {genomeReads, genomeLength};
    } else {
        std::cerr << "Error: Unable to read the first genome read." << std::endl;
        // Close the file
        inputFile.close();
        return {{}, 0}; // Return an empty vector and 0 length
    }
}

void processGenomeReads(const std::vector<std::string>& genomeReads, int k) {
    // Process or use the genome reads as needed
    for (const auto& read : genomeReads) {
        std::cout << "Genome Read: " << read << std::endl;
    }

    std::cout << "Length of each read (k): " << k << std::endl;
}

int main() {
    // Specify the filename
    std::string filename = "../files/reads.txt";

    // Read genome reads from the file
    auto result = readGenomeReads(filename);

    // Access the vector of genome reads and the length of each read
    std::vector<std::string> genomeReads = result.first;
    int k = result.second;

    // Process the genome reads
    processGenomeReads(genomeReads, k);
    std::cout << "Done! " << std::endl;
    return 0; // Return success code
}
