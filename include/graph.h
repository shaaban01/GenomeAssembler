#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

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

    int GetInDegree(const std::string &node) const
    {
        int inDegree = 0;
        for (const auto &entry : graph_)
        {
            if (entry.second.find(node) != entry.second.end())
            {
                inDegree++;
            }
        }
        return inDegree;
    }

    int GetOutDegree(const std::string &node) const
    {
        return graph_.at(node).size();
    }

    std::string FindStartNode() const
    {
        std::string startNode;
        for (const auto &node : GetNodes())
        {
            if (GetOutDegree(node) - GetInDegree(node) == 1)
            {
                return node;
            }
            if (GetOutDegree(node) > 0)
            {
                startNode = node;
            }
        }
        return startNode;
    }

    std::vector<std::string> FindEulerianPath()
    {
        std::unordered_map<std::string, std::unordered_set<std::string>> localGraph = graph_;
        std::vector<std::string> path, stack;
        stack.push_back(FindStartNode());

        while (!stack.empty())
        {
            std::string v = stack.back();
            if (localGraph[v].empty())
            {
                path.push_back(v);
                stack.pop_back();
            }
            else
            {
                std::string w = *localGraph[v].begin();
                stack.push_back(w);
                localGraph[v].erase(w);
            }
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    bool IsValidEulerianPath() const
    {
        int startNodes = 0, endNodes = 0;
        for (const auto &node : GetNodes())
        {
            int outMinusIn = GetOutDegree(node) - GetInDegree(node);
            if (outMinusIn > 1 || outMinusIn < -1)
            {
                return false;
            }
            if (outMinusIn == 1)
            {
                startNodes++;
            }
            else if (outMinusIn == -1)
            {
                endNodes++;
            }
        }
        return (startNodes == 0 && endNodes == 0) || (startNodes == 1 && endNodes == 1);
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

    std::vector<std::string> GenerateContigs(const std::vector<std::string> &eulerianPath, int k)
    {
        // TODO:: Implement this function
    }

private:
    std::unordered_map<std::string, std::unordered_set<std::string>> graph_;
};
