#include <iostream>

#include "gtest/gtest.h"

#include "graph\function\Function.h"
#include "graph\Graph.h"
#include "graph\GraphBuilder.h"
#include "graph\Node.h"

#include "GraphLibTestUtils.h"

namespace GraphLibraryTest
{
	using namespace graphlib::graph;
	using namespace graphlib::graph::function;

	TEST(graphBuilderTests, TestGraphNode)
	{ CREATE_MEMORY_SNAPSHOT{
		GraphBuilder gb{};
		Graph g = gb.build();
		unsigned expected_size = 0;
		EXPECT_EQ(0, g.order()) << "Graph order";
		EXPECT_EQ(0, g.size())  << "Graph size";
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(graphBuilderTests, TestGraphWithSingleNode)
	{ CREATE_MEMORY_SNAPSHOT{
		GraphBuilder gb{};
		gb.addNode(L"const-func", FunctionConstant::NAME);
		Graph g = gb.build();
		EXPECT_EQ(1, g.order()) << "Graph order";
		EXPECT_EQ(0, g.size())  << "Graph size";

		// move graph
		Graph moved_graph = std::move(g);
		EXPECT_EQ(1, moved_graph.order()) << "Graph order";
		EXPECT_EQ(0, moved_graph.size()) << "Graph size";

		Graph moved_constructed(std::move(moved_graph));
		EXPECT_EQ(1, moved_constructed.order()) << "Graph order";
		EXPECT_EQ(0, moved_constructed.size()) << "Graph size";
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(graphBuilderTests, TestGraphWithTwoNodesAddedById)
	{ CREATE_MEMORY_SNAPSHOT{
		GraphBuilder gb{};
		auto n0 = gb.addNode(L"const", FunctionConstant::NAME, 1);
		auto n1 = gb.addNode(L"oppos", FunctionOpposite::NAME);
		gb.addEdge(n0, n1);
		Graph g = gb.build();

		EXPECT_EQ(2, g.order()) << "Graph order";
		EXPECT_EQ(1, g.size())  << "Graph size";

		// move graph
		Graph moved_graph = std::move(g);
		EXPECT_EQ(2, moved_graph.order()) << "Graph order";
		EXPECT_EQ(1, moved_graph.size())  << "Graph size";

		Graph moved_constructed(std::move(moved_graph));
		EXPECT_EQ(2, moved_constructed.order()) << "Graph order";
		EXPECT_EQ(1, moved_constructed.size())  << "Graph size";
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(graphBuilderTests, TestGraphWithTwoNodesAddedByLabel)
	{ CREATE_MEMORY_SNAPSHOT {
		GraphBuilder gb{};
		Label l0{ L"const" };
		Label l1{ L"oppos" };
		gb.addNode(l0, FunctionConstant::NAME, 1);
		gb.addNode(l1, FunctionOpposite::NAME);
		gb.addEdge(l0, l1);
		Graph g = gb.build();

		EXPECT_EQ(2, g.order()) << "Graph order";
		EXPECT_EQ(1, g.size())  << "Graph size";

		// move graph
		Graph moved_graph = std::move(g);
		EXPECT_EQ(2, moved_graph.order()) << "Graph order";
		EXPECT_EQ(1, moved_graph.size()) << "Graph size";

		Graph moved_constructed(std::move(moved_graph));
		EXPECT_EQ(2, moved_constructed.order()) << "Graph order";
		EXPECT_EQ(1, moved_constructed.size()) << "Graph size";
	} ASSERT_MEMORY_SNAPSHOT }
}