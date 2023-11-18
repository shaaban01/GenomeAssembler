#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <memory>
#include "../include/kmerifier.h"

/**
 * @brief A class representing a De Bruijn graph.
 *
 * This class represents a De Bruijn graph, which is a directed graph used in
 * sequence assembly. It is constructed from a set of k-mers, and can be used
 * to generate contigs and perform an Eulerian walk.
 */
class DeBruijnGraph
{
public:
    /**
     * @brief Default constructor for DeBruijnGraph.
     */
    DeBruijnGraph();

    /**
     * @brief Constructor for DeBruijnGraph.
     *
     * @param kmf A KMerifier object used to generate k-mers.
     */
    DeBruijnGraph(KMerifier kmf);

    /**
     * @brief Connects the last node to the first node in the graph.
     */
    void connectLastAndFirst();

    /**
     * @brief Adds an edge to the graph.
     *
     * @param from The starting node of the edge.
     * @param to The ending node of the edge.
     */
    void addEdge(const std::string_view &from, const std::string_view &to);

    /**
     * @brief Adds a node to the graph.
     *
     * @param node The node to be added.
     */
    void addNode(const std::string_view &node);

    /**
     * @brief Checks if the graph contains a given node.
     *
     * @param node The node to check for.
     * @return True if the graph contains the node, false otherwise.
     */
    bool contains(const std::string_view &node);

    /**
     * @brief Counts the number of edges in the graph.
     */
    void countEdges();

    /**
     * @brief Creates the De Bruijn graph.
     */
    void createGraph();

    /**
     * @brief Generates contigs from an Eulerian path.
     *
     * @param eulerianPath The Eulerian path to generate contigs from.
     * @param k The length of the k-mers used to generate the graph.
     * @return A vector of contigs.
     */
    std::vector<std::string> GenerateContigs(const std::vector<std::string> &eulerianPath, int k);

    /**
     * @brief Prints the De Bruijn graph.
     */
    void printGraph();

    /**
     * @brief Performs an Eulerian walk on the graph.
     *
     * @return The Eulerian walk as a string.
     */
    std::string DoEulerianWalk();

private:
    std::unordered_map<std::string_view, std::vector<std::string_view>> graph_; /**< The graph represented as an unordered map. */
    std::unordered_map<int, std::string_view> nodes;                            /**< The nodes in the graph represented as an unordered map. */
    std::unordered_map<std::string_view, int> edgeCounts;                       /**< The number of edges for each node represented as an unordered map. */
    std::unique_ptr<KMerifier> kmf_;                                            /**< A unique pointer to a KMerifier object used to generate k-mers. */
};