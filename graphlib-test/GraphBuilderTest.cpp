#include "stdafx.h"
#include "GraphLibTestUtils.hpp"

#include <iostream>

#include "graph\function\Function.h"
#include "graph\Graph.h"
#include "graph\GraphBuilder.h"
#include "graph\Node.h"

namespace GraphLibraryTest
{
	using namespace graphlib::graph;
	using namespace graphlib::graph::function;

	TEST_CLASS(GraphBuilderTest)
	{
	public:
		TEST_METHOD(TestGraphNode)
		{
			CREATE_MEMORY_SNAPSHOT{
				GraphBuilder gb{};
				Graph g = gb.build();
				unsigned expected_size = 0;
				Assert::AreEqual(expected_size, g.order(), L"Graph order count doesn't match.", LINE_INFO());
				Assert::AreEqual(expected_size, g.size(), L"Graph size count doesn't match.", LINE_INFO());
			} ASSERT_MEMORY_SNAPSHOT
		}

		TEST_METHOD(TestGraphWithSingleNode)
		{
			CREATE_MEMORY_SNAPSHOT{
				GraphBuilder gb{};
				gb.addNode(L"const-func", FunctionConstant::NAME);
				Graph g = gb.build();
				unsigned expected_order = 1;
				Assert::AreEqual(expected_order, g.order(), L"Graph order count doesn't match.", LINE_INFO());
				unsigned expected_size = 0;
				Assert::AreEqual(expected_size, g.size(), L"Graph size count doesn't match.", LINE_INFO());

				// move graph
				Graph moved_graph = std::move(g);
				Assert::AreEqual(expected_order, moved_graph.order(), L"Moved graph order count doesn't match.", LINE_INFO());
				Assert::AreEqual(expected_size, moved_graph.size(), L"Moved graph size count doesn't match.", LINE_INFO());

				Graph moved_constructed(std::move(moved_graph));
				Assert::AreEqual(expected_order, moved_constructed.order(), L"Move constructed graph order count doesn't match.", LINE_INFO());
				Assert::AreEqual(expected_size, moved_constructed.size(), L"Move constructed graph size count doesn't match.", LINE_INFO());
			} ASSERT_MEMORY_SNAPSHOT
		}

		TEST_METHOD(TestGraphWithTwoNodesAddedById)
		{ CREATE_MEMORY_SNAPSHOT{
			GraphBuilder gb{};
			auto n0 = gb.addNode(L"const", FunctionConstant::NAME, 1);
			auto n1 = gb.addNode(L"oppos", FunctionOpposite::NAME);
			gb.addEdge(n0, n1);
			Graph g = gb.build();

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

		TEST_METHOD(TestGraphWithTwoNodesAddedByLabel)
		{ CREATE_MEMORY_SNAPSHOT{
			GraphBuilder gb{};
			Label l0{ L"const" };
			Label l1{ L"oppos" };
			gb.addNode(l0, FunctionConstant::NAME, 1);
			gb.addNode(l1, FunctionOpposite::NAME);
			gb.addEdge(l0, l1);
			Graph g = gb.build();

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