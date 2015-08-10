#include "GraphLibTestUtils.h"

#include <iostream>

#include "GraphTestHelper.h"

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
			Graph g = createTestGraph();

			unsigned expected_size = 0;
			auto order = algorithms::topologicalSort(g);
			EXPECT_EQ(2, order.size());
			EXPECT_EQ(Label{ L"const"}, order[0]->label());
			EXPECT_EQ(Label{ L"oppos"}, order[1]->label());
		} ASSERT_MEMORY_SNAPSHOT
	}
}