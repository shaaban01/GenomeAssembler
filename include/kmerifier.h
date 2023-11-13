// Description: Class that transforms reads into kmers.

#pragma once

#include <string>
#include <unordered_set>
#include <vector>

class KMerifier
{
public:
    KMerifier(int k_mer_size) : k_mer_size_(k_mer_size) {}

    // Transforms the input reads into a set of kmers.
    void TransformReadsToKmers(const std::vector<std::string> &reads)
    {
        for (const auto &read : reads)
        {
            for (int i = 0; i < read.size() - k_mer_size_ + 1; i++)
            {
                std::string kmer = read.substr(i, k_mer_size_);
                kmer_set_.insert(kmer);
            }
        }
    }

    // Returns a set of all kmers in the input reads.
    const std::unordered_set<std::string> &GetKmers() const
    {
        return kmer_set_;
    }

private:
    int k_mer_size_;
    std::unordered_set<std::string> kmer_set_;
};
