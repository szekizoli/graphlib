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

	TEST(graphBuilderTests, TestGraphOperatorPlus)
	{ CREATE_MEMORY_SNAPSHOT {
		GraphBuilder gb{};
		auto node_1 = gb.addNode(L"1", FunctionConstant::NAME, 1);
		auto node_2 = gb.addNode(L"2", FunctionConstant::NAME, 2);
		auto node_s = node_1 + node_2;
		Graph g = gb.build();

		EXPECT_EQ(3, g.order()) << "Graph order";
		EXPECT_EQ(2, g.size()) << "Graph size";

		{
			auto input_nodes = g.find_input_nodes();
			EXPECT_EQ(2, input_nodes.size()) << "input node's size";
			EXPECT_EQ(L"1", input_nodes[0]->label()) << "node 1 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[0]->function().name()) << "node + label";
			EXPECT_EQ(L"2", input_nodes[1]->label()) << "node 2 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[1]->function().name()) << "node + label";
		}
		{
			auto output_nodes = g.find_output_nodes();
			EXPECT_EQ(1, output_nodes.size()) << "output node's size";
			EXPECT_EQ(L"1+2", output_nodes[0]->label()) << "node + label";
			EXPECT_EQ(FunctionAdd::NAME, output_nodes[0]->function().name()) << "node + function name";
		}
		// move graph
		Graph moved_graph = std::move(g);
		EXPECT_EQ(3, moved_graph.order()) << "Graph order";
		EXPECT_EQ(2, moved_graph.size()) << "Graph size";

		Graph moved_constructed(std::move(moved_graph));
		EXPECT_EQ(3, moved_constructed.order()) << "Graph order";
		EXPECT_EQ(2, moved_constructed.size()) << "Graph size";
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(graphBuilderTests, TestGraphOperatorPlusMultiple)
	{ CREATE_MEMORY_SNAPSHOT {
		GraphBuilder gb{};
		auto node_1 = gb.addNode(L"1", FunctionConstant::NAME, 1);
		auto node_2 = gb.addNode(L"2", FunctionConstant::NAME, 2);
		auto node_3 = gb.addNode(L"3", FunctionConstant::NAME, 3);
		auto node_4 = gb.addNode(L"4", FunctionConstant::NAME, 4);
		auto node_s = node_1 + node_2 + node_3 + node_4;
		Graph g = gb.build();

		EXPECT_EQ(5, g.order()) << "Graph order";
		EXPECT_EQ(4, g.size()) << "Graph size";

		{
			auto input_nodes = g.find_input_nodes();
			EXPECT_EQ(4, input_nodes.size()) << "input node's size";
			EXPECT_EQ(L"1", input_nodes[0]->label()) << "node 1 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[0]->function().name()) << "node + label";
			EXPECT_EQ(L"2", input_nodes[1]->label()) << "node 2 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[1]->function().name()) << "node + label";
			EXPECT_EQ(L"3", input_nodes[2]->label()) << "node 3 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[2]->function().name()) << "node + label";
			EXPECT_EQ(L"4", input_nodes[3]->label()) << "node 4 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[3]->function().name()) << "node + label";
		}
		{
			auto output_nodes = g.find_output_nodes();
			EXPECT_EQ(1, output_nodes.size()) << "output node's size";
			EXPECT_EQ(L"1+2+3+4", output_nodes[0]->label()) << "node + label";
			EXPECT_EQ(FunctionAdd::NAME, output_nodes[0]->function().name()) << "node + function name";
		}
		// move graph
		Graph moved_graph = std::move(g);
		EXPECT_EQ(5, moved_graph.order()) << "Graph order";
		EXPECT_EQ(4, moved_graph.size()) << "Graph size";

		Graph moved_constructed(std::move(moved_graph));
		EXPECT_EQ(5, moved_constructed.order()) << "Graph order";
		EXPECT_EQ(4, moved_constructed.size()) << "Graph size";
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(graphBuilderTests, TestGraphOperatorMultiply)
	{ CREATE_MEMORY_SNAPSHOT {
		GraphBuilder gb{};
		auto node_1 = gb.addNode(L"1", FunctionConstant::NAME, 1);
		auto node_2 = gb.addNode(L"2", FunctionConstant::NAME, 2);
		auto node_s = node_1 * node_2;
		Graph g = gb.build();

		EXPECT_EQ(3, g.order()) << "Graph order";
		EXPECT_EQ(2, g.size()) << "Graph size";

		{
			auto input_nodes = g.find_input_nodes();
			EXPECT_EQ(2, input_nodes.size()) << "input node's size";
			EXPECT_EQ(L"1", input_nodes[0]->label()) << "node 1 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[0]->function().name()) << "node label";
			EXPECT_EQ(L"2", input_nodes[1]->label()) << "node 2 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[1]->function().name()) << "node label";
		}
		{
			auto output_nodes = g.find_output_nodes();
			EXPECT_EQ(1, output_nodes.size()) << "output node's size";
			EXPECT_EQ(L"1*2", output_nodes[0]->label()) << "node * label";
			EXPECT_EQ(FunctionMultiply::NAME, output_nodes[0]->function().name()) << "node * function name";
		}
		// move graph
		Graph moved_graph = std::move(g);
		EXPECT_EQ(3, moved_graph.order()) << "Graph order";
		EXPECT_EQ(2, moved_graph.size()) << "Graph size";

		Graph moved_constructed(std::move(moved_graph));
		EXPECT_EQ(3, moved_constructed.order()) << "Graph order";
		EXPECT_EQ(2, moved_constructed.size()) << "Graph size";
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(graphBuilderTests, TestGraphOperatorMultiplyMultiple)
	{ CREATE_MEMORY_SNAPSHOT {
		GraphBuilder gb{};
		auto node_1 = gb.addNode(L"1", FunctionConstant::NAME, 1);
		auto node_2 = gb.addNode(L"2", FunctionConstant::NAME, 2);
		auto node_3 = gb.addNode(L"3", FunctionConstant::NAME, 3);
		auto node_4 = gb.addNode(L"4", FunctionConstant::NAME, 4);
		auto node_s = node_1 * node_2 * node_3 * node_4;
		Graph g = gb.build();

		EXPECT_EQ(5, g.order()) << "Graph order";
		EXPECT_EQ(4, g.size()) << "Graph size";

		{
			auto input_nodes = g.find_input_nodes();
			EXPECT_EQ(4, input_nodes.size()) << "input node's size";
			EXPECT_EQ(L"1", input_nodes[0]->label()) << "node 1 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[0]->function().name()) << "node label";
			EXPECT_EQ(L"2", input_nodes[1]->label()) << "node 2 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[1]->function().name()) << "node label";
			EXPECT_EQ(L"3", input_nodes[2]->label()) << "node 3 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[2]->function().name()) << "node label";
			EXPECT_EQ(L"4", input_nodes[3]->label()) << "node 4 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[3]->function().name()) << "node label";
		}
		{
			auto output_nodes = g.find_output_nodes();
			EXPECT_EQ(1, output_nodes.size()) << "output node's size";
			EXPECT_EQ(L"1*2*3*4", output_nodes[0]->label()) << "node * label";
			EXPECT_EQ(FunctionMultiply::NAME, output_nodes[0]->function().name()) << "node * function name";
		}
		// move graph
		Graph moved_graph = std::move(g);
		EXPECT_EQ(5, moved_graph.order()) << "Graph order";
		EXPECT_EQ(4, moved_graph.size()) << "Graph size";

		Graph moved_constructed(std::move(moved_graph));
		EXPECT_EQ(5, moved_constructed.order()) << "Graph order";
		EXPECT_EQ(4, moved_constructed.size()) << "Graph size";
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(graphBuilderTests, TestGraphOperatorAddMultiply)
	{ CREATE_MEMORY_SNAPSHOT{
		GraphBuilder gb{};
		auto node_1 = gb.addNode(L"1", FunctionConstant::NAME, 1);
		auto node_2 = gb.addNode(L"2", FunctionConstant::NAME, 2);
		auto node_3 = gb.addNode(L"3", FunctionConstant::NAME, 3);
		auto node_4 = gb.addNode(L"4", FunctionConstant::NAME, 4);
		auto node_s = node_1 + node_2 * node_3 + node_4;
		Graph g = gb.build();

		EXPECT_EQ(6, g.order()) << "Graph order";
		EXPECT_EQ(5, g.size()) << "Graph size";

		{
			auto input_nodes = g.find_input_nodes();
			EXPECT_EQ(4, input_nodes.size()) << "input node's size";
			EXPECT_EQ(L"1", input_nodes[0]->label()) << "node 1 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[0]->function().name()) << "node + label";
			EXPECT_EQ(L"2", input_nodes[1]->label()) << "node 2 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[1]->function().name()) << "node + label";
			EXPECT_EQ(L"3", input_nodes[2]->label()) << "node 3 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[2]->function().name()) << "node + label";
			EXPECT_EQ(L"4", input_nodes[3]->label()) << "node 4 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[3]->function().name()) << "node + label";
		}
		{
			auto output_nodes = g.find_output_nodes();
			EXPECT_EQ(1, output_nodes.size()) << "output node's size";
			EXPECT_EQ(L"1+2*3+4", output_nodes[0]->label()) << "node + label";
			EXPECT_EQ(FunctionAdd::NAME, output_nodes[0]->function().name()) << "node + function name";
		}
		// move graph
		Graph moved_graph = std::move(g);
		EXPECT_EQ(6, moved_graph.order()) << "Graph order";
		EXPECT_EQ(5, moved_graph.size()) << "Graph size";

		Graph moved_constructed(std::move(moved_graph));
		EXPECT_EQ(6, moved_constructed.order()) << "Graph order";
		EXPECT_EQ(5, moved_constructed.size()) << "Graph size";
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(graphBuilderTests, TestGraphOperatorAddMultiply2)
	{ CREATE_MEMORY_SNAPSHOT{
		GraphBuilder gb{};
		auto node_1 = gb.addNode(L"1", FunctionConstant::NAME, 1);
		auto node_2 = gb.addNode(L"2", FunctionConstant::NAME, 2);
		auto node_3 = gb.addNode(L"3", FunctionConstant::NAME, 3);
		auto node_4 = gb.addNode(L"4", FunctionConstant::NAME, 4);
		auto node_s = node_1 * node_2 + node_3 * node_4;
		Graph g = gb.build();

		EXPECT_EQ(7, g.order()) << "Graph order";
		EXPECT_EQ(6, g.size()) << "Graph size";

		{
			auto input_nodes = g.find_input_nodes();
			EXPECT_EQ(4, input_nodes.size()) << "input node's size";
			EXPECT_EQ(L"1", input_nodes[0]->label()) << "node 1 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[0]->function().name()) << "node + label";
			EXPECT_EQ(L"2", input_nodes[1]->label()) << "node 2 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[1]->function().name()) << "node + label";
			EXPECT_EQ(L"3", input_nodes[2]->label()) << "node 3 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[2]->function().name()) << "node + label";
			EXPECT_EQ(L"4", input_nodes[3]->label()) << "node 4 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[3]->function().name()) << "node + label";
		}
		{
			auto output_nodes = g.find_output_nodes();
			EXPECT_EQ(1, output_nodes.size()) << "output node's size";
			EXPECT_EQ(L"1*2+3*4", output_nodes[0]->label()) << "node + label";
			EXPECT_EQ(FunctionAdd::NAME, output_nodes[0]->function().name()) << "node + function name";
		}
		// move graph
		Graph moved_graph = std::move(g);
		EXPECT_EQ(7, moved_graph.order()) << "Graph order";
		EXPECT_EQ(6, moved_graph.size()) << "Graph size";

		Graph moved_constructed(std::move(moved_graph));
		EXPECT_EQ(7, moved_constructed.order()) << "Graph order";
		EXPECT_EQ(6, moved_constructed.size()) << "Graph size";
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(graphBuilderTests, TestGraphOperatorAddMultiply3)
	{ CREATE_MEMORY_SNAPSHOT{
		GraphBuilder gb{};
		auto node_1 = gb.addNode(L"1", FunctionConstant::NAME, 1);
		auto node_2 = gb.addNode(L"2", FunctionConstant::NAME, 2);
		auto node_3 = gb.addNode(L"3", FunctionConstant::NAME, 3);
		auto node_4 = gb.addNode(L"4", FunctionConstant::NAME, 4);
		auto node_s = (node_1 + node_2) * (node_3 + node_4);
		Graph g = gb.build();

		EXPECT_EQ(7, g.order()) << "Graph order";
		EXPECT_EQ(6, g.size()) << "Graph size";

		{
			auto input_nodes = g.find_input_nodes();
			EXPECT_EQ(4, input_nodes.size()) << "input node's size";
			EXPECT_EQ(L"1", input_nodes[0]->label()) << "node 1 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[0]->function().name()) << "node + label";
			EXPECT_EQ(L"2", input_nodes[1]->label()) << "node 2 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[1]->function().name()) << "node + label";
			EXPECT_EQ(L"3", input_nodes[2]->label()) << "node 3 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[2]->function().name()) << "node + label";
			EXPECT_EQ(L"4", input_nodes[3]->label()) << "node 4 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[3]->function().name()) << "node + label";
		}
		{
			auto output_nodes = g.find_output_nodes();
			EXPECT_EQ(1, output_nodes.size()) << "output node's size";
			EXPECT_EQ(L"(1+2)*(3+4)", output_nodes[0]->label()) << "node * label";
			EXPECT_EQ(FunctionMultiply::NAME, output_nodes[0]->function().name()) << "node * function name";
		}
		// move graph
		Graph moved_graph = std::move(g);
		EXPECT_EQ(7, moved_graph.order()) << "Graph order";
		EXPECT_EQ(6, moved_graph.size()) << "Graph size";

		Graph moved_constructed(std::move(moved_graph));
		EXPECT_EQ(7, moved_constructed.order()) << "Graph order";
		EXPECT_EQ(6, moved_constructed.size()) << "Graph size";
	} ASSERT_MEMORY_SNAPSHOT }

	TEST(graphBuilderTests, TestGraphOperatorSqrt)
	{ CREATE_MEMORY_SNAPSHOT {
		GraphBuilder gb{};
		auto node_1 = gb.addNode(L"9", FunctionConstant::NAME, 1);
		auto node_s = sqrt(node_1);
		Graph g = gb.build();

		EXPECT_EQ(2, g.order()) << "Graph order";
		EXPECT_EQ(1, g.size()) << "Graph size";

		{
			auto input_nodes = g.find_input_nodes();
			EXPECT_EQ(1, input_nodes.size()) << "input node's size";
			EXPECT_EQ(L"9", input_nodes[0]->label()) << "node 1 label";
			EXPECT_EQ(FunctionConstant::NAME, input_nodes[0]->function().name()) << "node label";
		}
		{
			auto output_nodes = g.find_output_nodes();
			EXPECT_EQ(1, output_nodes.size()) << "output node's size";
			EXPECT_EQ(L"sqrt(9)", output_nodes[0]->label()) << "node sqrt label";
			EXPECT_EQ(FunctionSquareRoot::NAME, output_nodes[0]->function().name()) << "node sqrt function name";
		}
		// move graph
		Graph moved_graph = std::move(g);
		EXPECT_EQ(2, moved_graph.order()) << "Graph order";
		EXPECT_EQ(1, moved_graph.size()) << "Graph size";

		Graph moved_constructed(std::move(moved_graph));
		EXPECT_EQ(2, moved_constructed.order()) << "Graph order";
		EXPECT_EQ(1, moved_constructed.size()) << "Graph size";
	} ASSERT_MEMORY_SNAPSHOT }
}