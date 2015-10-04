#include <iostream>
#include <vector>

#include "gtest/gtest.h"
#include "GraphTestHelper.h"

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
		nodes.emplace_back(Node{ NodeId{ 0 }, L"const", function_ptr(new FunctionConstant(1)) });
		nodes.emplace_back(Node{ NodeId{ 1 }, L"oppos", function_ptr(new FunctionOpposite()) });
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

	TEST(graphTest, testInputNodes)
	{
		auto graph = createTestGraph();
		auto input = graph.find_input_nodes();
		EXPECT_EQ(1, input.size());
		auto node = input[0];
		EXPECT_EQ(Label{ L"const" }, node->label());
		EXPECT_EQ(FunctionConstant::NAME, node->function().name());
	}

	TEST(graphTest, testOutputNodes)
	{
		auto graph = createTestGraph();
		auto output = graph.find_output_nodes();
		EXPECT_EQ(1, output.size());
		auto node = output[0];
		EXPECT_EQ(Label{ L"oppos" }, node->label());
		EXPECT_EQ(FunctionOpposite::NAME, node->function().name());
	}

	TEST(graphTest, testIndexOperatorNodes)
	{
		Graph g = createQuadraticGraph();
		for (unsigned i = 0; i < g.order(); ++i) {
			const Node& n = g[i];
			EXPECT_EQ(i, n.id());
			EXPECT_EQ(g.nodes()[i].label(), n.label());
		}
	}
}