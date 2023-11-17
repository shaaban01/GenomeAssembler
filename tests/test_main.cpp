#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include "../include/graph.h"

class DeBruijnGraphTest : public ::testing::Test
{
protected:
    // Set up common resources for all tests
    void SetUp() override
    {
        // You may initialize common resources here if needed
    }

    // Clean up common resources for all tests
    void TearDown() override
    {
        // You may release common resources here if needed
    }

    // You can declare member variables accessible to all tests here
};

// Example test case
TEST_F(DeBruijnGraphTest, AddNodeEdge)
{
    DeBruijnGraph graph;
    graph.addNode("Node1");
    graph.addNode("Node2");
    graph.addEdge("Node1", "Node2");
    EXPECT_TRUE(graph.contains("Node1") && graph.contains("Node2"));
    EXPECT_TRUE(graph.getGraph_()["Node1"].front() == "Node2");
}

TEST_F(DeBruijnGraphTest, ConnectLastAndFirst)
{
    KMerifier kmerifier(3);
    std::vector<std::string> reads = {"AAGA"};
    kmerifier.TransformReadsToKmers(reads);
    DeBruijnGraph graph(kmerifier);

    graph.connectLastAndFirst();

    // graph.countEdges();

    graph.printGraph();
    EXPECT_TRUE(graph.getGraph_()["AA"].front() == "AG");
    EXPECT_TRUE(graph.getGraph_()["AG"].front() == "GA");
    EXPECT_TRUE(graph.getGraph_()["GA"].front() == "AA");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}