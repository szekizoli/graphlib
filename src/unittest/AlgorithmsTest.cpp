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
			auto order = algorithms::topologicalSort<Graph, Node>(g);
			EXPECT_EQ(2, order.size());
			EXPECT_EQ(Label{ L"const"}, order[0]->label());
			EXPECT_EQ(Label{ L"oppos"}, order[1]->label());
		} ASSERT_MEMORY_SNAPSHOT
	}

	TEST(algorithmsTests, TestCreatePredecessorCountWithEmptyGraph)
	{ CREATE_MEMORY_SNAPSHOT{
		Graph g = GraphBuilder{}.build();
		auto count = algorithms::predecessorCount<Graph, Node>(g);
		EXPECT_EQ(g.size(), count.size());
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(algorithmsTests, TestCreatePredecessorCountWithTestGraph)
	{ CREATE_MEMORY_SNAPSHOT{
		Graph g = createTestGraph();
		auto count = algorithms::predecessorCount<Graph, Node>(g);
		EXPECT_EQ(g.order(), count.size());
		EXPECT_EQ(0, count[0]);
		EXPECT_EQ(1, count[1]);
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(algorithmsTests, TestCreatePredecessorCountWithQuadraticGraph)
	{ CREATE_MEMORY_SNAPSHOT{
		Graph g = createQuadraticGraph();
		auto count = algorithms::predecessorCount<Graph, Node>(g);
		EXPECT_EQ(g.order(), count.size());
		for (int i = 0; i < g.order(); ++i) 
		{
			EXPECT_EQ(g[i].predecessorSize(), count[i]);
		}
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(algorithmsTests, CreateTopologicalSortQuadraticGraph)
	{
		CREATE_MEMORY_SNAPSHOT{
			Graph g = createQuadraticGraph();

			unsigned expected_size = 0;
			auto order = algorithms::topologicalSort<Graph, Node>(g);
			EXPECT_EQ(17, order.size());
			auto count = algorithms::predecessorCount<Graph, Node>(g);
			for (const auto& n : order)
			{
				EXPECT_EQ(0, count[n->id()]);// the predecessors left for this is 0.
				// decrement number of predecessors for successors
				for (const auto& s : n->successors()) {
					--count[s->id()];
				}
			}
		} ASSERT_MEMORY_SNAPSHOT
	}
}