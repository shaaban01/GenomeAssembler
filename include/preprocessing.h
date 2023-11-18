// Declare functions and classes for data preprocessing, including quality control and error correction(maybe later).
#ifndef GENOME_READER_H
#define GENOME_READER_H

#include <string>
#include <vector>

std::pair<std::vector<std::string>, int> readGenomeReads(const std::string& filename);
void processGenomeReads(const std::vector<std::string>& genomeReads, int k);

#endif  // GENOME_READER_H
