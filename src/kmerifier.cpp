#include "../include/kmerifier.h"
#include <iostream>

KMerifier::KMerifier() : k_mer_size_(0) {}

KMerifier::KMerifier(int k_mer_size) : k_mer_size_(k_mer_size) {}

int KMerifier::GetKmerSize() const
{
    return k_mer_size_;
}

void KMerifier::TransformReadsToKmers(const std::vector<std::string> &reads)
{
    int kmer_index = 0;
    for (const auto &read : reads)
    {
        for (int i = 0; i < read.size() - k_mer_size_ + 1; ++i)
        {
            std::string kmer = read.substr(i, k_mer_size_);
            kmer_map_[kmer_index] = kmer;
            ++kmer_index;
        }
    }
}

const std::unordered_map<int, std::string> KMerifier::GetKmers() const
{
    return kmer_map_;
}

std::unordered_map<int, std::string> KMerifier::GetKmersMinusOneMers()
{
    std::unordered_map<int, std::string> kmers;
    std::unordered_map<int, std::string> k_1_mers;
    kmers = GetKmers();
    for (int i = 0; i < kmers.size(); i++)
    {
        std::string km = kmers[i];
        k_1_mers[2 * i] = km.substr(0, k_mer_size_ - 1);
        k_1_mers[2 * i + 1] = km.substr(1, k_mer_size_ - 1);
    }
    return k_1_mers;
}

std::unordered_set<std::string> KMerifier::GetUniqueKMinusOneMers()
{
    std::unordered_map<int, std::string> kmers;
    std::unordered_map<int, std::string> k_1_mers;
    std::unordered_set<std::string> unique_k_1_mers;
    kmers = GetKmers();

    for (int i = 0; i < kmers.size(); i++)
    {
        std::string km = kmers[i];
        k_1_mers[2 * i] = km.substr(0, k_mer_size_ - 1);
        k_1_mers[2 * i + 1] = km.substr(1, k_mer_size_ - 1);
    }

    for (int i = 0; i < k_1_mers.size(); i++)
    {
        unique_k_1_mers.insert(k_1_mers[i]);
    }
    return unique_k_1_mers;
}