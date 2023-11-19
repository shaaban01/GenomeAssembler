#include "../include/kmerifier.h"

KMerifier::KMerifier() : k_mer_size_(0)
{
    kmer_vec_.reserve(1000000);
}

KMerifier::KMerifier(int k_mer_size) : k_mer_size_(k_mer_size)
{
    kmer_vec_.reserve(1000000);
}

int KMerifier::GetKmerSize() const
{
    return k_mer_size_;
}

#pragma omp declare reduction(merge : std::vector<std::string_view> : omp_out.insert(omp_out.end(), omp_in.begin(), omp_in.end()))
void KMerifier::TransformReadsToKmers(const std::vector<std::string> &reads)
{
    for (int r = 0; r < reads.size(); ++r)
    {
        const auto &read = reads[r];
        for (int i = 0; i < read.size() - k_mer_size_ + 1; ++i)
        {
            std::string_view kmer = std::string_view(read).substr(i, k_mer_size_);
            kmer_vec_.emplace_back(kmer);
        }
    }
}

std::vector<std::string_view> KMerifier::GetKmers() const
{
    return kmer_vec_;
}

#pragma omp declare reduction(merge : std::unordered_set<std::string_view> : omp_out.insert(omp_in.begin(), omp_in.end()))
std::vector<std::string_view> KMerifier::GetKmersMinusOneMers()
{
    std::vector<std::string_view> k_1_mers;
    k_1_mers.reserve(2 * kmer_vec_.size());
    for (int i = 0; i < kmer_vec_.size(); i++)
    {
        std::string_view km = kmer_vec_[i];
        k_1_mers.emplace_back(km.substr(0, k_mer_size_ - 1));
        k_1_mers.emplace_back(km.substr(1, k_mer_size_ - 1));
    }
    return k_1_mers;
}

std::unordered_set<std::string_view> KMerifier::GetUniqueKMinusOneMers()
{
    std::vector<std::string_view> k_1_mers;
    std::unordered_set<std::string_view> unique_k_1_mers;

    k_1_mers = GetKmersMinusOneMers();
#pragma omp parallel for reduction(merge : unique_k_1_mers)
    for (int i = 0; i < k_1_mers.size(); i++)
    {
        unique_k_1_mers.insert(k_1_mers[i]);
    }
    return unique_k_1_mers;
}