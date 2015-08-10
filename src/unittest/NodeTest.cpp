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

	TEST(nodeTest, testEmptyNode)
	{
		Node n;
		EXPECT_EQ(0, n.predecessorSize()) << "Node predecessor size should be zero.";
		EXPECT_EQ(0, n.successorSize()) << "Node successor size should be zero.";
	}

	TEST(nodeTest, testNodeWithEdge)
	{
		Node n0{ NodeId{ 0 }, L"const", functionptr(new FunctionConstant(1)) };
		Node n1{ NodeId{ 1 }, L"oppos", functionptr(new FunctionOpposite()) };
		make_edge(n0, n1);
		unsigned value_0 = 0;
		unsigned value_1 = 1;
		EXPECT_EQ(0, n0.predecessorSize()) << "Node predecessor size should be zero.";
		EXPECT_EQ(1, n0.successorSize()) << "Node successor size should be one.";
		EXPECT_EQ(1, n1.predecessorSize()) << "Node predecessor size should be one.";
		EXPECT_EQ(0, n1.successorSize()) << "Node successor size should be zero.";
	}
}