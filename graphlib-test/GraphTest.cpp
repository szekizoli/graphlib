#include "stdafx.h"
#include "GraphLibTestUtils.hpp"

#include <iostream>

#include "graph\function\Function.h"
#include "graph\Graph.h"
#include "graph\Node.h"

namespace GraphLibraryTest
{
	using namespace graphlib::graph;
	using namespace graphlib::graph::function;

	TEST_CLASS(GraphTest)
	{
	public:
		TEST_METHOD(TestGraphNode)
		{ CREATE_MEMORY_SNAPSHOT{
			Graph g;
			unsigned expected_size = 0;
			Assert::AreEqual(expected_size, g.order(), L"Graph order count doesn't match.", LINE_INFO());
			Assert::AreEqual(expected_size, g.size(), L"Graph size count doesn't match.", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }

		TEST_METHOD(TestGraphWithSingleNode)
		{ CREATE_MEMORY_SNAPSHOT{
			Graph g{ vector < Node >(1) };
			unsigned expected_order = 1;
			Assert::AreEqual(expected_order, g.order(), L"Graph order count doesn't match.", LINE_INFO());
			unsigned expected_size = 0;
			Assert::AreEqual(expected_size, g.size(), L"Graph size count doesn't match.", LINE_INFO());

			// move graph
			Graph moved_graph = std::move(g);
			Assert::AreEqual(expected_order, moved_graph.order(), L"Moved graph order count doesn't match.", LINE_INFO());
			Assert::AreEqual(expected_size, moved_graph.size(), L"Moved graph size count doesn't match.", LINE_INFO());

			Graph moved_constructed (std::move(moved_graph));
			Assert::AreEqual(expected_order, moved_constructed.order(), L"Move constructed graph order count doesn't match.", LINE_INFO());
			Assert::AreEqual(expected_size, moved_constructed.size(), L"Move constructed graph size count doesn't match.", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }

		TEST_METHOD(TestGraphWithTwoNodes)
		{ CREATE_MEMORY_SNAPSHOT{
			vector<Node> nodes;
			nodes.emplace_back(Node { NodeId{ 0 }, L"const", functionptr(new FunctionConstant(1)) });
			nodes.emplace_back(Node { NodeId{ 1 }, L"oppos", functionptr(new FunctionOpposite()) });
			make_edge(nodes[0], nodes[1]);
			Graph g { std::move(nodes) };

			unsigned expected_order = 2;
			Assert::AreEqual(expected_order, g.order(), L"Graph order count doesn't match.", LINE_INFO());
			unsigned expected_size = 1;
			Assert::AreEqual(expected_size, g.size(), L"Graph size count doesn't match.", LINE_INFO());

			// move graph
			Graph moved_graph = std::move(g);
			Assert::AreEqual(expected_order, moved_graph.order(), L"Moved graph order count doesn't match.", LINE_INFO());
			Assert::AreEqual(expected_size, moved_graph.size(), L"Moved graph size count doesn't match.", LINE_INFO());

			Graph moved_constructed(std::move(moved_graph));
			Assert::AreEqual(expected_order, moved_constructed.order(), L"Move constructed graph order count doesn't match.", LINE_INFO());
			Assert::AreEqual(expected_size, moved_constructed.size(), L"Move constructed graph size count doesn't match.", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }
	};
}