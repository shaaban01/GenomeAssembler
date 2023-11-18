#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

std::pair<std::vector<std::string>, int> readGenomeReads(const std::string &filename);
void processGenomeReads(const std::vector<std::string> &genomeReads, int k);
