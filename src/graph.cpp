#include "../include/graph.h"

DeBruijnGraph::DeBruijnGraph() = default;

DeBruijnGraph::DeBruijnGraph(KMerifier kmf)
    : kmf_(std::make_unique<KMerifier>(kmf))
{
    createGraph();
}

void DeBruijnGraph::connectLastAndFirst()
{
    // connects the last node with the first node
    std::string lastNode = nodes[nodes.size() - 1];
    std::string firstNode = nodes[0];

    addEdge(lastNode, firstNode);
}

void DeBruijnGraph::addEdge(const std::string &from, const std::string &to)
{
    graph_[from].push_back(to);
}

void DeBruijnGraph::addNode(const std::string &node)
{
    graph_[node] = {};
}

bool DeBruijnGraph::contains(const std::string &node)
{
    return graph_.find(node) != graph_.end();
}

void DeBruijnGraph::countEdges()
{
    for (const auto &[node, edgeList] : graph_)
    {
        edgeCounts[node] = edgeList.size();
    }
}

void DeBruijnGraph::createGraph()
{
    int nodesInserted = 0;
    int edgesInserted = 0;

    std::unordered_map<int, std::string> k_1_mers = kmf_->GetKmersMinusOneMers();

    for (int i = 0; i < k_1_mers.size(); i++)
    {
        if (!(contains(k_1_mers[i])))
        // if previous k-1-mer is not the same as this k-1-mer
        {
            // add that k-1-mer to the graph
            addNode(k_1_mers[i]);

            nodes[nodesInserted] = k_1_mers[i];
            nodesInserted++;
        }
    }

    // first connect the left k-1-mer to corresponding right-k-1-mer
    for (int i = 0; i < k_1_mers.size(); i += 2)
    {
        if (nodesInserted > 1)
        {
            edgesInserted++;
            addEdge(k_1_mers[i], k_1_mers[i + 1]);
        }
    }

    // then connect the previous right-k-1-mer to next left-k-1-mer
    for (int i = 1; i < k_1_mers.size() - 1; i += 2)
    {
        if (k_1_mers[i] == k_1_mers[i + 1])
            continue;

        if (nodesInserted > 1)
        {
            edgesInserted++;
            addEdge(k_1_mers[i], k_1_mers[i + 1]);
        }
    }
}

std::vector<std::string> DeBruijnGraph::GenerateContigs(const std::vector<std::string> &eulerianPath, int k)
{
    std::vector<std::string> contigs;
    contigs.push_back(eulerianPath[0]);
    for (int p = 1; p < eulerianPath.size(); ++p)
    {
        if (eulerianPath[p].substr(0, k - 2) == eulerianPath[p - 1].substr(1, k - 1))
            contigs[contigs.size() - 1] += eulerianPath[p][k - 2];
        else
            contigs.push_back(eulerianPath[p]);
    }
    return contigs;
}

void DeBruijnGraph::printGraph()
{
    for (const auto &[node, edgeList] : graph_)
    {
        std::cout << node << " -> ";
        for (const auto &edge : edgeList)
        {
            std::cout << edge << " ";
        }
        std::cout << std::endl;
    }
}

std::string DeBruijnGraph::DoEulerianWalk()
{
    std::string original = "";

    // Connect the last and first nodes to create a circuit
    connectLastAndFirst();

    // Create temporary copies of the graph and edge counts
    std::unordered_map<std::string, std::vector<std::string>> adjListTemp = graph_;

    countEdges();

    std::unordered_map<std::string, int> edgeCountsTemp = edgeCounts;

    // If the graph is empty, return an empty string
    if (adjListTemp.size() == 0)
    {
        original = "";
        return original;
    }

    // Use a stack to backtrack and a vector to store the final circuit
    std::stack<std::string> currPath;
    std::vector<std::string> circuit;

    // Start from the first node
    currPath.push(nodes[0]);
    std::string currNode = nodes[0];

    // Perform the Eulerian walk
    while (!currPath.empty())
    {
        // Check if the current node has edges we can traverse
        if (edgeCountsTemp[currNode] != 0)
        {
            currPath.push(currNode);

            // Get the next node to traverse
            std::string nextNode = adjListTemp[currNode].back();

            // Decrement the edge count for the current node
            edgeCountsTemp[currNode]--;

            // Remove the edge from the adjacency list
            adjListTemp[currNode].pop_back();

            // Traverse to the next node
            currNode = nextNode;
        }

        // If the current node has no more remaining edges,
        // add it to the final circuit and backtrack
        else
        {
            circuit.push_back(currNode);

            // Backtrack to the previous node
            currNode = currPath.top();
            currPath.pop();
        }
    }

    // Reverse the circuit to get the correct order
    reverse(circuit.begin(), circuit.end());

    // --- Restoration of the original string ---

    // Add the first node to the original string
    original = circuit[0];

    // Iterate over the remaining nodes in the circuit
    int k = kmf_->GetKmerSize();
    for (int i = 1; i < (circuit.size() - 1); i++)
    {
        // Check if there is an overlap between the previous and current node
        std::string right_prev = std::string(circuit[i - 1].begin() + 1, circuit[i - 1].end());
        std::string left_curr = std::string(circuit[i].begin(), circuit[i].end() - 1);
        if ((k - 1 > 1) && (right_prev == left_curr))
        {
            // If there is an overlap, append the last character only
            std::string curr = circuit[i];
            original += curr[curr.size() - 1];
        }
        else
        {
            // Otherwise, append the entire node
            original += circuit[i];
        }
    }

    return original;
}