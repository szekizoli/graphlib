
#include <iostream>
#include <vector>

#include "gtest/gtest.h"

#include "graph\function\Function.h"
#include "graph\Graph.h"
#include "graph\Node.h"

namespace GraphLibraryTest
{
	using std::vector;
	using namespace graphlib::graph;
	using namespace graphlib::graph::function;

	TEST(graphTest, testEmptyGraph)
	{
		Graph g;
		EXPECT_EQ(0, g.size()) << "Graph size should be zero.";
		EXPECT_EQ(0, g.order()) << "Graph order should be zero.";
	}

	TEST(graphTest, testGraphWithSingleNode)
	{
		Graph g{ vector < Node >(1) };
		EXPECT_EQ(1, g.order()) << "Graph order count doesn't match.";
		EXPECT_EQ(0, g.size()) << "Graph size count doesn't match.";

		// move graph
		Graph moved_graph = std::move(g);
		EXPECT_EQ(1, moved_graph.order()) << "Graph order count doesn't match.";
		EXPECT_EQ(0, moved_graph.size()) << "Graph size count doesn't match.";

		Graph moved_constructed(std::move(moved_graph));
		EXPECT_EQ(1, moved_constructed.order()) << "Graph order count doesn't match.";
		EXPECT_EQ(0, moved_constructed.size()) << "Graph size count doesn't match.";
	}

	TEST(graphTest, testGraphWithTwoNodes)
	{
		vector<Node> nodes;
		nodes.emplace_back(Node{ NodeId{ 0 }, L"const", functionptr(new FunctionConstant(1)) });
		nodes.emplace_back(Node{ NodeId{ 1 }, L"oppos", functionptr(new FunctionOpposite()) });
		make_edge(nodes[0], nodes[1]);
		Graph g{ std::move(nodes) };
		EXPECT_EQ(2, g.order()) << "Graph order count doesn't match.";
		EXPECT_EQ(1, g.size()) << "Graph size count doesn't match.";

		// move graph
		Graph moved_graph = std::move(g);
		EXPECT_EQ(2, moved_graph.order()) << "Graph order count doesn't match.";
		EXPECT_EQ(1, moved_graph.size()) << "Graph size count doesn't match.";

		Graph moved_constructed(std::move(moved_graph));
		EXPECT_EQ(2, moved_constructed.order()) << "Graph order count doesn't match.";
		EXPECT_EQ(1, moved_constructed.size()) << "Graph size count doesn't match.";
	}
}