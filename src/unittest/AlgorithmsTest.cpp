#include "GraphLibTestUtils.hpp"

#include <iostream>

#include "graph\Algorithms.h"
#include "graph\Graph.h"
#include "graph\GraphBuilder.h"
#include "graph\Node.h"
#include "graph\function\Function.h"

namespace GraphLibraryTest
{
	using namespace graphlib::graph;
	using namespace graphlib::graph::function;

	TEST(algorithmsTests, TestCreateTopologicalSort)
	{
		CREATE_MEMORY_SNAPSHOT{
			/*GraphBuilder gb{};
			Graph g = gb.build();
			auto res = algorithms::topologicalSort<Graph, Node>(g);*/

			unsigned expected_size = 0;
			//Assert::AreEqual(expected_size, g.order(), L"Graph order count doesn't match.", LINE_INFO());
			//Assert::AreEqual(expected_size, g.size(), L"Graph size count doesn't match.", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT
	}
}