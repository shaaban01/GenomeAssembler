// Define the data structures for the De Bruijn graph, including classes for nodes and edges.
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <string_view>

namespace debruijn
{

    /**
     * @brief A class representing a node in a De Bruijn graph.
     *
     */
    class Node
    {
    public:
        /**
         * @brief Construct a new Node object with the given k-mer.
         *
         * @param kmer The k-mer represented by this node.
         */
        Node(const std::string &kmer) : kmer_(kmer) {}

        /**
         * @brief Get the k-mer represented by this node.
         *
         * @return const std::string& The k-mer represented by this node.
         */
        const std::string &kmer() const { return kmer_; }

        /**
         * @brief Add an outgoing edge to the given next k-mer.
         *
         * @param next_kmer The next k-mer in the sequence.
         */
        void addOutgoingEdge(const std::string &next_kmer)
        {
            outgoing_edges_.insert(next_kmer);
        }

        /**
         * @brief Add an incoming edge from the given previous k-mer.
         *
         * @param prev_kmer The previous k-mer in the sequence.
         */
        void addIncomingEdge(const std::string &prev_kmer)
        {
            incoming_edges_.insert(prev_kmer);
        }

        /**
         * @brief Get the set of outgoing edges from this node.
         *
         * @return const std::unordered_set<std::string>& The set of outgoing edges from this node.
         */
        const std::unordered_set<std::string> &outgoingEdges() const
        {
            return outgoing_edges_;
        }

        /**
         * @brief Get the set of incoming edges to this node.
         *
         * @return const std::unordered_set<std::string>& The set of incoming edges to this node.
         */
        const std::unordered_set<std::string> &incomingEdges() const
        {
            return incoming_edges_;
        }

    private:
        std::string kmer_;
        std::unordered_set<std::string> outgoing_edges_;
        std::unordered_set<std::string> incoming_edges_;
    };

    /**
     * @brief A class representing a De Bruijn graph.
     *
     */
    class Graph
    {
    public:
        /**
         * @brief Construct a new Graph object with the given k-mer size.
         *
         * @param k The size of the k-mers in the graph.
         */
        Graph(int k) : k_(k) {}

        /**
         * @brief Add a read to the graph.
         *
         * @param read The read to add to the graph.
         */
        void addRead(const std::string &read)
        {
            for (int i = 0; i <= read.length() - k_; i++)
            {
                std::string kmer = read.substr(i, k_);
                std::string next_kmer = read.substr(i + 1, k_ - 1);
                if (nodes_.count(kmer) == 0)
                {
                    nodes_[kmer] = Node(kmer);
                }
                if (nodes_.count(next_kmer) == 0)
                {
                    nodes_[next_kmer] = Node(next_kmer);
                }
                nodes_[kmer].addOutgoingEdge(next_kmer);
                nodes_[next_kmer].addIncomingEdge(kmer);
            }
        }

        /**
         * @brief Get the map of nodes in the graph.
         *
         * @return const std::unordered_map<std::string, Node>& The map of nodes in the graph.
         */
        const std::unordered_map<std::string, Node> &nodes() const
        {
            return nodes_;
        }

    private:
        int k_;
        std::unordered_map<std::string, Node> nodes_;
    };

} // namespace debruijn
