#include "../include/preprocessing.h"
#include <omp.h>

#pragma omp declare reduction(merge : std::vector<std::string> : omp_out.insert(omp_out.end(), omp_in.begin(), omp_in.end()))
std::pair<std::vector<std::string>, int> readGenomeReads(const std::string &filename)
{

    std::ifstream inputFile(filename);

    constexpr size_t BUFFER_SIZE = 512 * 1024;
    char buffer[BUFFER_SIZE];

    inputFile.rdbuf()->pubsetbuf(buffer, BUFFER_SIZE);

    // Check if the file is opened successfully
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file."
                  << "\n";
        return {{}, 0}; // Return an empty vector and 0 length
    }

    // Read the first genome read from the file
    std::string firstGenomeRead;
    if (std::getline(inputFile, firstGenomeRead))
    {
        // Get the length of the genome from the first read
        int genomeLength = firstGenomeRead.length();

        // Display the length of the genome
        std::cout << "Genome Length: " << genomeLength << "\n";

        // Reset the file pointer to the beginning of the file for subsequent reads
        inputFile.clear();
        inputFile.seekg(0, std::ios::beg);

        // Read and store the rest of the genome reads
        std::vector<std::string> genomeReads;
        std::string genomeRead;
        while (std::getline(inputFile, genomeRead))
        {
            if (genomeRead.length() < genomeLength)
            {
                genomeLength = genomeRead.length();
            }
            genomeReads.push_back(genomeRead);
        }

        // Close the file
        inputFile.close();

        // Return the vector of genome reads and the length of each read
        return {genomeReads, genomeLength};
    }
    else
    {
        std::cerr << "Error: Unable to read the first genome read."
                  << "\n";
        // Close the file
        inputFile.close();
        return {{}, 0}; // Return an empty vector and 0 length
    }
}

void processGenomeReads(const std::vector<std::string> &genomeReads, int k)
{
    // Process or use the genome reads as needed
    for (const auto &read : genomeReads)
    {
        std::cout << "Genome Read: " << read << "\n";
    }

    std::cout << "Length of each read (k): " << k << "\n";
}
