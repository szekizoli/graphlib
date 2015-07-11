#include "stdafx.h"
#include "GraphLibTestUtils.hpp"

#include <iostream>

#include "graph\function\Function.h"
#include "graph\Node.h"

namespace GraphLibraryTest
{
	using namespace graphlib::graph;
	using namespace graphlib::graph::function;

	TEST_CLASS(NodeTest)
	{
	public:
		TEST_CLASS_INITIALIZE(InitFunctionBuilderTest) {
			Function::init();
		}

		TEST_METHOD(TestEmptyNode)
		{ CREATE_MEMORY_SNAPSHOT {
			Node n;
			unsigned expected_size = 0;
			Assert::AreEqual(expected_size, n.predecessorSize(), L"", LINE_INFO());
			Assert::AreEqual(expected_size, n.successorSize(), L"", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }

		TEST_METHOD(TestNodeWithEdge)
		{ CREATE_MEMORY_SNAPSHOT{
			Node n0{ NodeId{ 0 }, L"const", functionptr(new FunctionConstant(1)) };
			Node n1{ NodeId{ 1 }, L"oppos", functionptr(new FunctionOpposite()) };
			make_edge(n0, n1);
			unsigned value_0 = 0;
			unsigned value_1 = 1;
			Assert::AreEqual(value_0, n0.predecessorSize(), L"", LINE_INFO());
			Assert::AreEqual(value_1, n0.successorSize(), L"", LINE_INFO());
			Assert::AreEqual(value_1, n1.predecessorSize(), L"", LINE_INFO());
			Assert::AreEqual(value_0, n1.successorSize(), L"", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }
	};
}