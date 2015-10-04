#include "GraphLibTestUtils.h"

#include <algorithm>
#include <iostream>

#include "GraphTestHelper.h"

#include "graph\Algorithms.h"
#include "graph\Graph.h"
#include "graph\GraphBuilder.h"
#include "graph\Node.h"
#include "executor\Executor.h"
#include "graph\function\Function.h"

namespace GraphLibraryTest
{
	using namespace graphlib::executor;
	using namespace graphlib::graph;
	using namespace graphlib::graph::function;

	TEST(executorTests, TestSimpleExecutorWithTestGraph)
	{ CREATE_MEMORY_SNAPSHOT{
		Graph g = createTestGraph();
		const vector<NodePtr> order = algorithms::topologicalSort<Graph, Node>(g);
		Result result = execute(order.begin(), order.end());
		EXPECT_DOUBLE_EQ( 1.0, result[0]);
		EXPECT_DOUBLE_EQ(-1.0, result[1]);
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(executorTests, TestSimpleExecutorWithQuadraticGraph)
	{ CREATE_MEMORY_SNAPSHOT{
		Graph g = createQuadraticGraph(1.0, 3.0, 2.0);
		const vector<NodePtr> order = algorithms::topologicalSort<Graph, Node>(g);
		//auto result = tmpexecute(order.begin(), order.end(), Result(order.size()));
		auto result = tmpexecute(order.begin(), order.end(), vector<function::Value>(order.size()));
		EXPECT_DOUBLE_EQ(-2.0, result[15]);
		EXPECT_DOUBLE_EQ(-1.0, result[16]);
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(executorTests, TestSimpleExecutorWithOpBuilderAddMul1)
	{ CREATE_MEMORY_SNAPSHOT{
		GraphBuilder gb{};
		auto node_1 = gb.add_node(L"2", FunctionConstant::NAME, 2);
		auto node_2 = gb.add_node(L"3", FunctionConstant::NAME, 3);
		auto node_3 = gb.add_node(L"5", FunctionConstant::NAME, 5);
		auto node_4 = gb.add_node(L"7", FunctionConstant::NAME, 7);
		auto node_s = node_1 + node_2 * node_3 + node_4;
		Graph g = gb.build();

		const vector<NodePtr> order = algorithms::topologicalSort<Graph, Node>(g);
		Result result = execute(order.begin(), order.end());
		EXPECT_DOUBLE_EQ(15, result[4]);
		EXPECT_DOUBLE_EQ(24, result[5]);
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(executorTests, TestSimpleExecutorWithOpBuilderAddMul2)
	{ CREATE_MEMORY_SNAPSHOT{
		GraphBuilder gb{};
		auto node_1 = gb.add_node(L"2", FunctionConstant::NAME, 2);
		auto node_2 = gb.add_node(L"3", FunctionConstant::NAME, 3);
		auto node_3 = gb.add_node(L"5", FunctionConstant::NAME, 5);
		auto node_4 = gb.add_node(L"7", FunctionConstant::NAME, 7);
		auto node_s = node_1 * node_2 + node_3 * node_4;
		Graph g = gb.build();

		const vector<NodePtr> order = algorithms::topologicalSort<Graph, Node>(g);
		Result result = execute(order.begin(), order.end());
		EXPECT_EQ(7, result.size()) << "Result size doesn't match";
		// the order of result[4] and resulr[5] may not be determined
		// in aspect of use-case this doesn't matter, because this isn't about the end result
		vector<double> results{ result[4], result[5] };
		std::sort(results.begin(), results.end());
		EXPECT_DOUBLE_EQ(6, results[0]);
		EXPECT_DOUBLE_EQ(35, results[1]);
		EXPECT_DOUBLE_EQ(41, result[6]);
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(executorTests, TestSimpleExecutorWithOpBuilderAddMul3)
	{ CREATE_MEMORY_SNAPSHOT{
		GraphBuilder gb{};
		auto node_1 = gb.add_node(L"2", FunctionConstant::NAME, 2);
		auto node_2 = gb.add_node(L"3", FunctionConstant::NAME, 3);
		auto node_3 = gb.add_node(L"5", FunctionConstant::NAME, 5);
		auto node_4 = gb.add_node(L"7", FunctionConstant::NAME, 7);
		auto node_s = (node_1 + node_2) * (node_3 + node_4);
		Graph g = gb.build();

		const vector<NodePtr> order = algorithms::topologicalSort<Graph, Node>(g);
		Result result = execute(order.begin(), order.end());
		EXPECT_EQ(7, result.size()) << "Result size doesn't match";
		// the order of result[4] and resulr[5] may not be determined
		// in aspect of use-case this doesn't matter, because this isn't about the end result
		vector<double> results{ result[4], result[5] };
		std::sort(results.begin(), results.end());
		EXPECT_DOUBLE_EQ(5, results[0]);
		EXPECT_DOUBLE_EQ(12, results[1]);
		EXPECT_DOUBLE_EQ(60, result[6]);
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(executorTests, TestSimpleExecutorWithOpBuilderAddMul4)
	{ CREATE_MEMORY_SNAPSHOT{
		GraphBuilder gb{};
		auto node_1 = gb.add_node(L"2", FunctionConstant::NAME, 2);
		auto node_2 = gb.add_node(L"3", FunctionConstant::NAME, 3);
		auto node_3 = gb.add_node(L"5", FunctionConstant::NAME, 5);
		auto node_4 = gb.add_node(L"7", FunctionConstant::NAME, 7);
		auto node_s = node_1 * (node_2 + node_3) * node_4;
		Graph g = gb.build();

		const vector<NodePtr> order = algorithms::topologicalSort<Graph, Node>(g);
		Result result = execute(order.begin(), order.end());
		EXPECT_EQ(6, result.size()) << "Result size doesn't match";
		EXPECT_DOUBLE_EQ(2, result[0]);
		EXPECT_DOUBLE_EQ(3, result[1]);
		EXPECT_DOUBLE_EQ(5, result[2]);
		EXPECT_DOUBLE_EQ(7, result[3]);
		EXPECT_DOUBLE_EQ(8, result[4]);
		EXPECT_DOUBLE_EQ(112, result[5]);
	} ASSERT_MEMORY_SNAPSHOT }
}