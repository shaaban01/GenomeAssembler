#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>

class DeBruijnGraph
{
public:
    DeBruijnGraph(const std::unordered_set<std::string> &kmers)
    {
        for (const auto &kmer : kmers)
        {
            std::string prefix = kmer.substr(0, kmer.size() - 1);
            std::string suffix = kmer.substr(1);
            graph_[prefix].insert(suffix);
        }
    }

    // Returns the set of all nodes in the de Bruijn graph.
    const std::unordered_set<std::string> &GetNodes() const
    {
        static std::unordered_set<std::string> nodes;
        for (const auto &entry : graph_)
        {
            nodes.insert(entry.first);
            for (const auto &edge : entry.second)
            {
                nodes.insert(edge);
            }
        }
        return nodes;
    }

    // Returns the set of all outgoing edges from a given node.
    const std::unordered_set<std::string> &GetOutgoingEdges(const std::string &node) const
    {
        return graph_.at(node);
    }

    void printGraph()
    {
        for (const auto &[node, edgeList] : graph_)
        {
            std::cout << node << " -> ";
            for (const auto &edge : edgeList)
            {
                std::cout << edge << ",";
            }
            std::cout << std::endl;
        }
    }

private:
    std::unordered_map<std::string, std::unordered_set<std::string>> graph_;
};
