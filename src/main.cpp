#include <iostream>
#include "../include/kmerifier.h"
#include "../include/graph.h"

int main()
{
    KMerifier kmerifier(4);
    std::vector<std::string> reads = {"AAGATTCTCTAAGA"};

    kmerifier.TransformReadsToKmers(reads);
    DeBruijnGraph graph(kmerifier.GetKmers());
    graph.printGraph();
    std::cout << "Start node: " << graph.FindStartNode() << std::endl;
    std::cout << "Eulerian path: ";
    for (const auto &node : graph.FindEulerianPath())
    {
        std::cout << node << " ";
    }
    std::cout << std::endl;
    std::cout << "Is valid Eulerian path: " << graph.IsValidEulerianPath() << std::endl;

    for (const auto node : graph.GenerateContigs(graph.FindEulerianPath(), 4))
    {
        std::cout << node << std::endl;
    }
    return 0;
}